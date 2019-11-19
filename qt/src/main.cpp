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


#include <QApplication>
#include <QString>
#include "mainWindow.h"

MainWindow* mainWindow = NULL;

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   mainWindow = new MainWindow;
   
   if (mainWindow->init(argc, argv))
   {
      mainWindow->show();
      return app.exec();
   }
   return -1;
}

extern "C" {
   void printMMCMessage(const char* message, ...)
   {
      va_list args;
      va_start(args, message);

      QString messageString;
      messageString.vsprintf(message, args);

      // send verbose messages across thread using the invoke system
      QMetaObject::invokeMethod(mainWindow, "onMessageReceived", Qt::QueuedConnection, Q_ARG(QString, messageString));

      va_end(args);
   }
}
