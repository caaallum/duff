AC_PREREQ([2.69])
AC_INIT([duff], [0.1.0], [caaallum])

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE([1.9.6 -Wall -Werror subdir-objects dist-bzip2 dist-xz])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_PATH_PROG(TAR, tar, /bin/tar)
AC_PROG_INSTALL

PKG_CHECK_MODULES([CURL], [libcurl])
PKG_CHECK_MODULES([CJSON], [libcjson])
PKG_CHECK_MODULES([CHECK], [check])
PKG_CHECK_MODULES([GLIB], [glib-2.0])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])

AC_OUTPUT
