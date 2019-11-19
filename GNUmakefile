# Copyright (c) 2006-2011 Nedko Arnaudov <nedko@arnaudov.name>,
#                         Alex Montgomery <apmontgo@users.sourceforge.net>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; version 2 of the License.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA



prefix ?= /usr/local
datarootdir ?= ${prefix}/share
exec_prefix ?= ${prefix}
bindir  ?= ${exec_prefix}/bin

QMAKE   = /usr/share/qt4/bin/qmake
INSTALL = /usr/bin/install -c
PKG_CFLAGS  += -g -O2 -I/usr/include/alsa
LIBS    += -L/usr/local/lib -L/usr/lib  -ljack -lasound -lX11

OBJECTS=main.o common.o

default:  qjackmmc
install:  gui_install
uninstall:  gui_uninstall

.SUFFIXES : .o .c

.c.o :
	$(CC) $(CFLAGS) $(PKG_CFLAGS) -c $<

jackctlmmc: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(PKG_CFLAGS) $(LIBS) -o $@

qjackmmc:
	cd qt && $(QMAKE) -o Makefile qjackmmc.pro && $(MAKE)


cli_install: jackctlmmc
	$(INSTALL) -v -D -m 0755 ./jackctlmmc $(DESTDIR)$(bindir)/jackctlmmc

gui_install: qjackmmc
	$(INSTALL) -v -D -m 0755 ./qjackmmc $(DESTDIR)$(bindir)/qjackmmc
	$(INSTALL) -v -D -m 0644 qt/images/qjackmmc.png $(DESTDIR)$(datarootdir)/pixmaps/qjackmmc.png
	$(INSTALL) -v -D -m 0644 qt/qjackmmc.desktop $(DESTDIR)$(datarootdir)/applications/qjackmmc.desktop

cli_uninstall:
	rm -vf $(DESTDIR)$(bindir)/jackctlmmc

gui_uninstall:
	rm -vf $(DESTDIR)$(bindir)/qjackmmc
	rm -vf $(DESTDIR)$(datarootdir)/pixmaps/qjackmmc.png
	rm -vf $(DESTDIR)$(datarootdir)/applications/qjackmmc.desktop

clean:
	rm -f jackctlmmc
	rm -f qjackmmc
	rm -rf *.o
	if test -f qt/Makefile ; then cd qt && $(MAKE) clean && rm Makefile src/Makefile ; fi

rebuild: clean default
