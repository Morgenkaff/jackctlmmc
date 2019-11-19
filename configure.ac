#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(QjackMMC, 4, apmontgo@users.sourceforge.net, qjackmmc)
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])

AC_PREFIX_DEFAULT(/usr/local)
ac_prefix=$prefix
if test "x$ac_prefix" = "xNONE"; then
    ac_prefix=$ac_default_prefix
fi
AC_SUBST(ac_prefix)
AC_DEFINE_UNQUOTED(CONFIG_PREFIX, ["$ac_prefix"], [Default installation prefix.])

ac_icon_dir="$ac_prefix/share/pixmaps"
AC_DEFINE_UNQUOTED(ICON_DIR, ["$ac_icon_dir"], [Default icon directory.])

ac_cflags="$ac_cflags -Wall"
ac_build_jackctlmmc="yes"
ac_build_qjackmmc="yes"

# Enable debugging argument option.
AC_ARG_ENABLE(debug,
  AC_HELP_STRING([--enable-debug], [enable debugging (default=no)]),
  [ac_debug="$enableval"])

if test "x$ac_debug" = "xyes"; then
   ac_debug="debug"
else
   ac_debug="release"
fi

AC_SUBST(ac_debug)

# check if the user wants QJackMMC built
AC_ARG_ENABLE(gui,
  AC_HELP_STRING([--enable-gui], [build the gui program qjackmmc (default=yes)]),
  [ac_build_qjackmmc="$enableval"],
  [ac_build_qjackmmc="yes"])

# check if the user wants jackctlmmc built
AC_ARG_ENABLE(cli,
  AC_HELP_STRING([--enable-cli], [build the command line program jackctlmmc (default=yes)]),
  [ac_build_jackctlmmc="$enableval"],
  [ac_build_jackctlmmc="yes"])

AC_PATH_PROG(PKG_CONFIG,pkg-config,no)

# Standard installation base dirs.
ac_with_paths="/usr /usr/local"

# Some a-la-debian alternatives...
for X in /usr/lib /usr/lib64 /usr/share; do
  for Y in qt qt4; do
    if test -d $X/$Y/bin; then
      ac_with_paths="$ac_with_paths $X/$Y"
    fi
  done
done

# Set for alternate Qt installation dir.
AC_ARG_WITH(qt,
  AC_HELP_STRING([--with-qt=PATH], [use alternate Qt install path]),
  [ac_with_paths="$ac_with_paths $withval"])

# Set for alternate JACK installation dir.
AC_ARG_WITH(jack,
  AC_HELP_STRING([--with-jack=PATH], [use alternate JACK install path]),
  [ac_with_paths="$ac_with_paths $withval"])

# Set for alternate ALSA installation dir.
AC_ARG_WITH(alsa,
  AC_HELP_STRING([--with-alsa=PATH], [use alternate ALSA install path]),
  [ac_with_paths="$ac_with_paths $withval"])

# Set for alternate LASH installation dir.
AC_ARG_WITH(lash,
  AC_HELP_STRING([--with-lash=PATH], [use alternate LASH install path]),
  [ac_with_paths="$ac_with_paths $withval"])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_INSTALL

# Checks for languages.
AC_LANG_C
AC_LANG_CPLUSPLUS

# Prepend alternate dependencies paths.
ac_path=$PATH
for X in $ac_with_paths; do
  if test -d $X/bin; then
    ac_path="$X/bin:$ac_path"
  fi
  if test -x $X/qmake; then
    ac_path="$X:$ac_path"
  fi
  if test -d $X/lib64; then
    ac_libs="-L$X/lib64 $ac_libs"
  fi
  if test -d $X/lib; then
    ac_libs="-L$X/lib $ac_libs"
  fi
done


PKG_PROG_PKG_CONFIG

# Check for JACK and ALSA libraries.
PKG_CHECK_MODULES([REQUIREDPKGS], [jack >= 0.99.0 alsa >= 1.0.0])
ac_cflags="$CFLAGS $REQUIREDPKGS_CFLAGS"
ac_libs="$ac_libs $REQUIREDPKGS_LIBS"
ac_pkgs="alsa jack"

# Check for proper Qt version.
if test "x$ac_build_qjackmmc" = "xyes"; then
   PKG_CHECK_MODULES(QT_UP_TO_DATE, [QtCore >= 4.4], [], [ac_build_qjackmmc="no"])

   # A common error message:
   ac_errmsg="not found in current PATH. Maybe QT development environment isn't available (qt-devel). QJackMMC cannot be built."

   # Check for Qt qmake utility.
   AC_PATH_PROG(ac_qmake, qmake, [no], $ac_path)
   if test "x$ac_qmake" = "xno"; then
      AC_MSG_WARN([*** qmake $ac_errmsg])
      ac_build_qjackmmc="no"
   fi
   AC_SUBST(ac_qmake)

   # Check for Qt moc utility.
   AC_PATH_PROG(ac_moc, moc, [no], $ac_path)
   if test "x$ac_moc" = "xno"; then
      AC_MSG_WARN([*** moc $ac_errmsg])
      ac_build_qjackmmc="no"
   fi
   AC_SUBST(ac_moc)

   # Check for Qt uic utility.
   AC_PATH_PROG(ac_uic, uic, [no], $ac_path)
   if test "x$ac_uic" = "xno"; then
      AC_MSG_WARN([*** uic $ac_errmsg])
      ac_build_qjackmmc="no"
   fi
   AC_SUBST(ac_uic)
fi # ac_build_qjackmmc

if test "x$ac_build_qjackmmc" = "xyes"; then
   AC_DEFINE(ENABLE_QJACKMMC, 1, [Define if QJackMMC can be built.])
   ac_libs="$ac_libs -lX11"
else
   AC_DEFINE(ENABLE_QJACKMMC, 0, [Define if QJackMMC can be built.])
fi

ac_default_deps=""
ac_default_install=""
ac_default_uninstall=""

if test "x$ac_build_jackctlmmc" = "xyes"; then
   ac_default_deps="jackctlmmc"
   ac_default_install="cli_install"
   ac_default_uninstall="cli_uninstall"
fi

if test "x$ac_build_qjackmmc" = "xyes"; then
   ac_default_deps="$ac_default_deps qjackmmc"
   ac_default_install="$ac_default_install gui_install"
   ac_default_uninstall="$ac_default_uninstall gui_uninstall"
fi

if test "x$ac_default_deps" = "x"; then
   AC_MSG_ERROR([both jackctlmmc and qjackmmc have been disabled, either voluntarily or by missing dependencies, bailing out.])
fi

AC_SUBST(ac_default_deps)
AC_SUBST(ac_default_install)
AC_SUBST(ac_default_uninstall)


# Check for JACK headers.
AC_CHECK_HEADER(jack/jack.h, [ac_jack_h="yes"], [ac_jack_h="no"])
if test "x$ac_jack_h" = "xno"; then
   AC_MSG_ERROR([JACK headers not found.])
fi

# Check for ALSA headers and ultimately
# for ALSA/MIDI sequencer support.
if test "x$ac_alsa_seq" = "xyes"; then
   AC_CHECK_HEADER(alsa/asoundlib.h, [ac_alsa_h="yes"], [ac_alsa_h="no"])
   if test "x$ac_alsa_h" = "xyes"; then
      AC_DEFINE(CONFIG_ALSA_SEQ, 1, [Define if ALSA/MIDI sequencer support is enabled.])
   else
      AC_MSG_ERROR([*** ALSA headers not found.])
   fi
fi

# check if the user wants LASH support
AC_ARG_ENABLE(lash,
  AC_HELP_STRING([--enable-lash], [enable LASH support (default=yes)]),
  [ac_lashsupport="$enableval"],
  [ac_lashsupport="yes"])

# check if the user wants JACK midi support
AC_ARG_ENABLE(jackmidi,
  AC_HELP_STRING([--enable-jackmidi], [enable JACK MIDI support (default=yes)]),
  [ac_jack_midi="$enableval"],
  [ac_jack_midi="yes"])

# Check for JACK MIDI headers availability.
if test "x$ac_jack_midi" = "xyes"; then
   AC_CHECK_HEADER(jack/midiport.h, [ac_jack_midi="yes"], [ac_jack_midi="no"])
   if test "x$ac_jack_midi" = "xyes"; then
      AC_DEFINE(JACK_MIDI_SUPPORT, 1, [Define if JACK MIDI support is available.])
   else
      AC_DEFINE(JACK_MIDI_SUPPORT, 0, [Define if JACK MIDI support is available.])
      AC_MSG_WARN([*** jack/midiport.h file not found.])
      AC_MSG_WARN([*** JACK 0.103.0 or later may be required.])
      AC_MSG_WARN([*** JACK MIDI support will be disabled.])
   fi
else
   AC_DEFINE(JACK_MIDI_SUPPORT, 0, [Define if JACK MIDI support is available.])
fi

PKG_CHECK_MODULES(LASH, lash-1.0 >= 0.5.0, have_lash="yes", have_lash="no")
if test "x$ac_lashsupport" = "xyes"; then
   if test "$have_lash" = "yes"; then
      AC_DEFINE(LASH_SUPPORT, 1, [Has lash.h])
      ac_cflags="$ac_cflags $LASH_CFLAGS"
      ac_libs="$ac_libs $LASH_LIBS"
      ac_pkgs="$ac_pkgs lash-1.0"
   else
      AC_MSG_WARN([LASH not found, session support will not be built.])
      AC_DEFINE(LASH_SUPPORT, 0, [Has lash.h])
   fi
   else
      AC_MSG_WARN([LASH intentionally disabled.])
      AC_DEFINE(LASH_SUPPORT, 0, [Has lash.h])
fi

# export makefile variables
AC_SUBST(ac_libs)
AC_SUBST(ac_cflags)
AC_SUBST(ac_pkgs)

# Checks for library functions.
AC_CHECK_FUNCS(system)

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([strtol])

AC_CONFIG_FILES([GNUmakefile qt/qjackmmc.desktop qt/src/src.pro])
AC_OUTPUT
