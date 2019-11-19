/*
 * Control JACK transport using MMC (MIDI)
 *
 * Copyright (c) 2006,2007,2008,2010 Nedko Arnaudov <nedko@arnaudov.name>
 * Copyright (c) 2008 Alex Montgomery <apmontgomery@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; version 2 of the License.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "common.h"

// exported globals
int g_quit = 0; // a flag which will be set by our signal handler when it's time to exit

// globals used only here in common.c
snd_seq_t* g_seq_ptr = NULL;
jack_client_t* g_jack_client = NULL;
struct pollfd* g_pollDescriptor = NULL;
int g_numDescriptors = 0;

#if LASH_SUPPORT
lash_client_t* g_lashc = NULL;

void init_lash(int argc, char* argv[])
{
   /* LASH setup */
   g_lashc = lash_init( lash_extract_args(&argc, &argv), "jackctlmmc", 0, LASH_PROTOCOL_VERSION); 

   if (g_lashc == NULL)
   {
      printMMCMessage("Failed to connect to LASH. Session management will not occur.\n");
   }
   
   // register JACK and ALSA clients with lash
   lash_alsa_client_id(g_lashc, snd_seq_client_id(g_seq_ptr));
   lash_jack_client_name(g_lashc, "jackctlmmc");
}

void process_lash_event(lash_event_t * event_ptr)
{
   enum LASH_Event_Type type;
   const char * str;

   type = lash_event_get_type(event_ptr);
   str = lash_event_get_string(event_ptr);

   switch (type)
   {
      case LASH_Quit:
         printMMCMessage("LASH_Quit received.\n");
         g_lashc = NULL;
         g_quit = 1;
         break;
      case LASH_Save_File:
      case LASH_Restore_File:
      case LASH_Save_Data_Set:
      default:
         printMMCMessage("LASH Event. Type = %u, string = \"%s\"\n",
               (unsigned int)type,
               (str == NULL)?"":str);
   }
}

void process_lash_config(lash_config_t * config_ptr)
{
   const char * key;
   const void * data;
   size_t data_size;

   key = lash_config_get_key(config_ptr);
   data = lash_config_get_value(config_ptr);
   data_size = lash_config_get_value_size(config_ptr);

   printMMCMessage("LASH Config. Key = \"%s\"\n", key);
}
#endif // LASH_SUPPORT

#if JACK_MIDI_SUPPORT

jack_port_t* g_jackMidiIn = NULL;

int jack_process_cb(jack_nframes_t numFrames, void* cbContext)
{
   uint8_t* inBuffer = 0;
   int numMidiEvents = 0;
   jack_midi_event_t currEvent;
   int midiIndex = 0;
   MidiSettings* settings = (MidiSettings*) cbContext;

   inBuffer = jack_port_get_buffer(g_jackMidiIn, numFrames);
   numMidiEvents = jack_midi_get_event_count(inBuffer);

   for (midiIndex = 0; midiIndex < numMidiEvents; ++midiIndex)
   {
      jack_midi_event_get(&currEvent, inBuffer, midiIndex);
      handle_midi(currEvent.buffer, settings);
   }

   return 0;
}

int init_jack_midi(MidiSettings* settings)
{
   int errorCode = 0;

   errorCode = jack_set_process_callback(g_jack_client, &jack_process_cb, settings);
   g_jackMidiIn = jack_port_register(g_jack_client, "in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput | JackPortIsTerminal, 1024);
   return (errorCode == 0 && g_jackMidiIn != 0);
}
#endif // JACK_MIDI_SUPPORT

int init_alsa_sequencer(const char* appName)
{
   snd_seq_port_info_t * seq_port_info = NULL;
   int ret = 0;

   /* ALSA sequencer initialisation */
   ret = snd_seq_open( &g_seq_ptr, "default", SND_SEQ_OPEN_INPUT, 0);
   if (ret < 0)
      return ret;

   // setup alsa sequencer port
   snd_seq_port_info_alloca(&seq_port_info);
   snd_seq_port_info_set_capability(seq_port_info, SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE);
   snd_seq_port_info_set_type( seq_port_info, SND_SEQ_PORT_TYPE_APPLICATION);
   snd_seq_port_info_set_midi_channels(seq_port_info, 16);
   snd_seq_port_info_set_port_specified(seq_port_info, 1);
   snd_seq_port_info_set_name(seq_port_info, "midi in");
   snd_seq_port_info_set_port(seq_port_info, 0);

   ret = snd_seq_create_port(g_seq_ptr, seq_port_info);

   if (ret < 0)
      printMMCMessage("Error with alsa sequencer initialization, %s\n", snd_strerror(ret));
   else // all is well, register the sequencer with whatever name was passed in
   {
      snd_seq_set_client_name(g_seq_ptr, appName);

      g_numDescriptors = snd_seq_poll_descriptors_count(g_seq_ptr, POLLIN);
      g_pollDescriptor = (struct pollfd *)malloc(g_numDescriptors * sizeof(struct pollfd));
      snd_seq_poll_descriptors(g_seq_ptr, g_pollDescriptor, g_numDescriptors, POLLIN);
   }

   return ret;
}

int init_jack(const char* appName)
{
   jack_status_t status;
   g_jack_client = jack_client_open(appName, JackNoStartServer, &status);

   if (!g_jack_client) // something went wrong
      return -1; // todo: check status to see exactly what happened

   return 0;
}

int activate_jack()
{
   /* tell jack that we are ready to do our thing */
   return jack_activate(g_jack_client);
}

void handle_midi(uint8_t* midiBuff, MidiSettings* settings)
{
   if (midiBuff[0] == 0xF0 && midiBuff[1] == 0x7F && midiBuff[3] == 0x06)
   {
      const uint8_t messageDeviceID = midiBuff[2];
      if (messageDeviceID == settings->deviceID)
      {
         const char mmcCommand = midiBuff[4];
         switch (mmcCommand)
         {
            case 1:                 /* stop */
               if (settings->verbose)
                  printMMCMessage("MMC Stop -> JACK transport stop\n");
               jack_transport_stop(g_jack_client);
               break;
            case 2:                 /* play */
            case 3:                 /* deferred play */
               if (settings->verbose)
                  printMMCMessage("MMC Play -> JACK transport start\n");
               jack_transport_start(g_jack_client);
               break;
            case 4:
               if (settings->verbose)
                  printMMCMessage("MMC Fast Forward -> Ignored\n");
               break;
            case 5:                 /* rewind */
               if (settings->verbose)
                  printMMCMessage("MMC Play -> JACK transport locate to 0\n");
               jack_transport_locate(g_jack_client, 0);
               break;
            case 6:
               if (settings->verbose)
                  printMMCMessage("MMC Record Strobe (Punch In) -> Ignored\n");
               break;
            case 7:
               if (settings->verbose)
                  printMMCMessage("MMC Record Exit (Punch out) -> Ignored\n");
               break;
            case 8:
               if (settings->verbose)
                  printMMCMessage("MMC Record Ready (Record Pause) -> Ignored\n");
               break;
            case 9:                 /* pause */
               if (settings->verbose)
                  printMMCMessage("MMC Pause -> JACK transport stop\n");
               jack_transport_stop(g_jack_client);
               break;
            case 0x44:              /* goto */
               if (midiBuff[5] == 0x06 && midiBuff[6] == 0x01)
               {
                  // some devices call hour 0 "60". Mask off the upper bits
                  uint8_t hour = (midiBuff[7] & 0x1f);
                  uint8_t minute = midiBuff[8];
                  uint8_t second = midiBuff[9];
                  uint8_t frame = midiBuff[10];
                  uint8_t subframe = midiBuff[11]; // percentage of a frame: 0 - 99
                  jack_position_t jack_pos;

                  // get Jack's current framerate and position
                  jack_transport_query(g_jack_client, &jack_pos);
                  uint32_t jack_frame_rate = jack_pos.frame_rate;
                  uint32_t jack_time_ms = (jack_pos.frame * 1000) / jack_frame_rate;
                  uint32_t device_time_ms = ((subframe * 10) / settings->frameRate + // subframe == 1/100th of a frame
                        (frame * 1000) / settings->frameRate +
                        (second * 1000) +
                        (minute * 60 * 1000) +
                        (hour * 60 * 60 * 1000));

                  // difference in milliseconds from JACK's reported transport to the MIDI goto's time
                  uint32_t jitter = (device_time_ms > jack_time_ms ? (device_time_ms - jack_time_ms) : (jack_time_ms - device_time_ms));

                  if (settings->verbose)
                     printMMCMessage("MMC goto hour: %d, min: %d, sec: %d, frame: %d, subframe: %d\n",
                           hour,
                           minute,
                           second,
                           frame,
                           subframe);

                  // check if the JACK clock is far enough away from the MMC time to care
                  if (jitter > settings->jitterTolerance)
                  {  // it is, change it.
                     jack_pos.valid = 0; // only the frame number will be valid since that's all we're changing

                     // need a placeholder so that we can keep precision while not letting the integer overflow
                     uint64_t placeholder =  (uint64_t)device_time_ms * jack_frame_rate / 1000;
                     jack_pos.frame = placeholder;

                     jack_transport_reposition(g_jack_client, &jack_pos);
                  }
                  else if (settings->verbose)
                     printMMCMessage("New position is within jitter range, ignoring. (%d ms)\n", jitter);
               }
               break;
            case 0x48:              /* step */
               {
                  int step;
                  jack_position_t jack_pos;

                  step = midiBuff[6];
                  if (step > 0x40)
                  {
                     step &= 0x3F;
                     step = -step;
                  }

                  if (settings->verbose)
                     printMMCMessage("MMC Step %d\n", step);

                  // get Jack's current framerate and position
                  jack_transport_query(g_jack_client, &jack_pos);

                  jack_pos.valid = 0; // only the frame number will be valid since that's all we're changing

                  jack_pos.frame += (int64_t)step * (int64_t)jack_pos.frame_rate / (int64_t)10;

                  jack_transport_reposition(g_jack_client, &jack_pos);
               }
               break;
            default:
               if (settings->verbose)
                  printMMCMessage("unsupported MMC command: 0x%x\n", mmcCommand);
         }
      }
      else if (settings->verbose)
      {
         printMMCMessage("MMC command received for device ID %x while listening for commands from device ID %x. Have you specified the correct device ID to listen to?\n",
                messageDeviceID,
                settings->deviceID);

      }
   }
}

uint8_t* get_midi_input ()
{
   snd_seq_event_t * seq_event_ptr = NULL;

#if LASH_SUPPORT
   /* Process LASH events */
   {
      lash_event_t * lash_event_ptr = NULL;
      lash_config_t * lash_config_ptr = NULL;
      while ((lash_event_ptr = lash_get_event(g_lashc)) != NULL)
      {
         process_lash_event(lash_event_ptr);
         lash_event_destroy(lash_event_ptr);
      }

      /* Process LASH configs */
      while ((lash_config_ptr = lash_get_config(g_lashc)) != NULL)
      {
         process_lash_config(lash_config_ptr);
         lash_config_destroy(lash_config_ptr);
      }
   }
#endif

   if (poll(g_pollDescriptor, g_numDescriptors, 250) > 0 && snd_seq_event_input(g_seq_ptr, &seq_event_ptr) >= 0 && seq_event_ptr->type == SND_SEQ_EVENT_SYSEX)
      return ((uint8_t *)seq_event_ptr->data.ext.ptr);

   return 0;
}

void cleanup_globals()
{
   int ret = 0;

   if (g_jack_client)
   {
#if JACK_MIDI_SUPPORT
      jack_port_unregister(g_jack_client, g_jackMidiIn);
#endif
      jack_deactivate(g_jack_client);
      jack_client_close(g_jack_client);
   }

   if (g_seq_ptr)
   {
      ret = snd_seq_close(g_seq_ptr);
      if (ret < 0)
      {
         printMMCMessage("Cannot close sequncer, %s\n", snd_strerror(ret));
      }
   }

   if (g_pollDescriptor)
      free(g_pollDescriptor);
}
