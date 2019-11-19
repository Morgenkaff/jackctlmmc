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

#ifndef COMMON_H
#define COMMON_H

#include <jack/jack.h>
#include <jack/transport.h>

#include <jack/types.h>
#include <jack/midiport.h>
#include <alsa/asoundlib.h>
#include "config.h"

typedef struct
{
    uint32_t frameRate;
    uint32_t jitterTolerance;
    int verbose;
    uint8_t deviceID;
} MidiSettings;

// globals
extern int g_quit;

// functions implemented differently by cli and qt frontends
extern void printMMCMessage(const char* message, ...);

// common functions
int init_alsa_sequencer(const char* appName);
int init_jack(const char* appName);
int activate_jack();
uint8_t* get_midi_input ();
void cleanup_globals();
void handle_midi(uint8_t* midiBuff, MidiSettings* settings);

#if LASH_SUPPORT
   #include <lash/lash.h>
   extern lash_client_t* g_lashc;
   void init_lash(int argc, char* argv[]);
   void process_lash_event(lash_event_t * event_ptr);
   void process_lash_config(lash_config_t * config_ptr);
#endif // LASH_SUPPORT

#if JACK_MIDI_SUPPORT
   #include <jack/midiport.h>
   int init_jack_midi(MidiSettings* settings); //< returns true when successful
#endif // JACK_MIDI_SUPPORT

#endif // COMMON_H
