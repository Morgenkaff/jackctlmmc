/***************************************************************************
 *   Copyright (C) 2009 by Alex Montgomery and Nedko Arnaudov   *
 *   check@Adaon   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "sequencerThread.h"
#include <QMutexLocker>
#include <QPointer>

SequencerThread::SequencerThread(QObject* parent, MidiSettings* settings, QMutex* settingsMutex)
   : QThread(parent), m_settings(settings), m_settingsMutex(settingsMutex), m_shouldExit(0)
{
}

void SequencerThread::listen(bool realTime)
{
   // note: this probably won't actually be an RT thread, but it's as close as QThread will allow
   if (realTime)
      start(QThread::TimeCriticalPriority);
   else
      start();
}

void SequencerThread::run ()
{
   g_quit = 0;
   quint8* midiData = 0;

   QPointer <SequencerThread> stillAlive(this);
   while(!g_quit && !stillAlive.isNull() && !m_shouldExit)
   {
      midiData = get_midi_input();
      if (midiData && !stillAlive.isNull())
      {
         QMutexLocker settingsLocker(m_settingsMutex);
         handle_midi(midiData, m_settings);
      }
   }

   // not ideal, but we need to dispose of ourself once we're out of the loop. If we don't
   // calling deleteLater from mainWindow after SequencerThread::die still causes a segfault
   deleteLater();
}

void SequencerThread::die()
{
   m_shouldExit = 1;
}
