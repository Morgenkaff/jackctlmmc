/* -*- Mode: C ; c-basic-offset: 3 -*- */
/*
 * Control JACK transport using MMC (MIDI)
 *
 * Copyright (c) 2006,2007,2008 Nedko Arnaudov <nedko@arnaudov.name>
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

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void printMMCMessage(const char* message, ...)
{
   va_list args;
   va_start(args, message);

   vprintf(message, args);

   va_end(args);
}

/* the signal handler */
void signalled(int signal)
{
   g_quit = 1;
}

// foward declares
void process_command_line(int argc, char *argv[], MidiSettings* settings);
void cleanup();

int main(int argc, char *argv[])
{
   int ret = 0;

   MidiSettings settings;
   
   // frame rate (frames per second) of the MMC controlling device
   settings.frameRate = 30; // command line equivalent: -f 30

   // jitter tolerance in milliseconds
   settings.jitterTolerance = 50; //command line: -t 50 

   settings.deviceID = 0x7f; // command line -d 7f

   settings.verbose = 0; // pass -v on the command line to turn this on
   
   // read the jitter tolerance, verbose setting, and device frame rate from command line
   process_command_line(argc, argv, &settings);

   printMMCMessage("%s starting with a jitter tolerance of %d milliseconds and a device frame rate of %d per second listening for device %x.\n", 
          argv[0], settings.jitterTolerance, settings.frameRate, settings.deviceID);

   // setup our signal handler signalled() above, so we can exit cleanly
   signal(SIGINT, signalled);

   ret = init_alsa_sequencer("jackctlmmc");
   if (ret < 0)
   {
      printMMCMessage("couldn't initialize alsa sequencer, the show won't go on...\n");
      cleanup();
      exit(0);
   }

   if (init_jack("jackctlmmc") < 0)
   {
      printMMCMessage("couldn't connect to jack server. Either it's not running or the client name is already taken\n");
      cleanup();
      exit(0);
   }

#if LASH_SUPPORT
   init_lash(argc, argv);
#endif // LASH_SUPPORT

#if JACK_MIDI_SUPPORT
   if (!init_jack_midi(&settings))
      printMMCMessage("could not initialize JACK MIDI, alsa port may still work...\n");
#endif

   activate_jack();

   while (!g_quit)
   {
      uint8_t* midiData = get_midi_input();
      if (midiData)
         handle_midi(midiData, &settings);
   }

   // so we shall quit, eh? ok, cleanup time. otherwise jack would probably produce an xrun on shutdown
   cleanup();

   if (settings.verbose)
      printMMCMessage("exited normally\n");

   return 0;
}


void process_command_line(int argc, char *argv[], // IN parameters
                          MidiSettings* midiSettings) // OUT parameters
{
   int parameter;
   long value;
   while ((parameter = getopt(argc, argv, "f:t:d:v")) != -1)
   {
      switch (parameter)
      {
         case 'v': 
            midiSettings->verbose = 1;
            break;
         case 'f':
            value = strtol(optarg, 0, 10);
            midiSettings->frameRate = (uint32_t)value;
            break;
         case 't':
            value = strtol(optarg, 0, 10);
            midiSettings->jitterTolerance = (uint32_t)value;
            break;
         case 'd':
            value = strtol(optarg, 0, 16);
            if (value >= 0 && value <= 255)
               midiSettings->deviceID = (uint8_t)value;
            break;
         case '?':
            printMMCMessage("usage: %s -f <device_frames_per_second> -t <jitter_tolerance_in_ms> -d <device_id_in_hexadecimal>\n", argv[0]);
            exit(1);
            break;
      }
   }
}

void cleanup()
{
   printMMCMessage("cleaning up...\n");
   cleanup_globals();
}
