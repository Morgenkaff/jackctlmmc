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

#include "ui_qjackmmc.h"
#include "../../config.h"

#include <QFile>
#include <QMutex>
#include <QPointer>

extern "C" {
#include "../../common.h"
}

class QValidator;
class SequencerThread;

#define QJACKMMC_CONFIG "/.qjackmmc"

class MainWindow : public QMainWindow, public Ui::QjackMMC
{
   Q_OBJECT

   public:
      MainWindow();
      bool init(int argc, char *argv[]);
      
   public slots:
      // these are autoconnected by virtue of their naming convention. QT4 voodoo
      void on_actionQuit_triggered();
      void on_actionWhat_triggered();
      void on_actionAbout_triggered();
      void on_loadButton_clicked();
      void on_saveButton_clicked();

      // input validator slots
      void onValidateFps();
      void onValidateJitter();
      void onValidateDeviceID();

      // checkbox slots
      void onVerboseChanged(bool checked);
      void onRealtimeChanged(bool checked);

      // other slots
      void onMessageReceived(QString message);
      
   protected:
      bool initSound(int argc, char *argv[]);
      void loadConfig(QFile& loadFile);
      void setDefaultSettings();

      // QT reimplementations
      void closeEvent(QCloseEvent* event);
      
      QPointer<SequencerThread> m_sequencerThread;
      MidiSettings m_settings; //< shared between threads, Always lock m_settingsMutex when accessing!
      QMutex m_settingsMutex; //< guards m_settings
};
