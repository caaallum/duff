AC_PREREQ([2.69])
AC_INIT([duff], [0.1.0], [callum@spei.rs])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE([1.9.6 -Wall -Werror subdir-objects dist-bzip2 dist-xz])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

dnl Check for programs
AM_PROG_AR
AC_PROG_CC
AC_PATH_PROG(TAR, tar, /bin/tar)
AC_PROG_INSTALL
LT_INIT

dnl Check for dependencies
PKG_CHECK_MODULES([GLIB], [glib-2.0])
PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([CJSON], [libcjson])
PKG_CHECK_MODULES([CHECK], [check])

dnl Option params
AC_ARG_ENABLE(output,
    AS_HELP_STRING([--enable-output], [Show log output]),
    AC_DEFINE([LOG_ENABLED], [], [Show log output]),
    AC_DEFINE([LOG_DISABLED], [], [Dont show log output])
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile lib/Makefile cli/Makefile test/Makefile])

AC_OUTPUT
