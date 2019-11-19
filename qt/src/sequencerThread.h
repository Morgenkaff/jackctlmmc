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

#include <QThread>
#include <QAtomicInt>

class QMutex;

extern "C" {
#include "../../common.h"
}

class SequencerThread : public QThread
{
   Q_OBJECT
         
   public: 
      SequencerThread(QObject* parent, MidiSettings* settings, QMutex* settingsMutex);
      
      void listen(bool realTime);
      void die();
      
   protected:
      virtual void run ();
      
      MidiSettings* m_settings;
      QMutex* m_settingsMutex;

      QAtomicInt m_shouldExit; //< atomic int used as bool
};
