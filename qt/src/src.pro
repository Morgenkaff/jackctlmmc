SOURCES += main.cpp \
 mainWindow.cpp \
 ../../common.c \
 validator.cpp \
 sequencerThread.cpp

HEADERS += mainWindow.h \
 validator.h \
 sequencerThread.h \
 ../../common.h \
 ../../config.h

FORMS += qjackmmc.ui

TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
	  release \
          link_pkgconfig

PKGCONFIG += alsa jack
TARGET = qjackmmc
DESTDIR = ../../
QT += gui

QMAKE_CFLAGS += $$(CFLAGS)
QMAKE_CXXFLAGS += $$(CFLAGS)
