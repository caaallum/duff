bin_PROGRAMS = duff

duff_SOURCES = duff.c \
			   args.c \
			   args.h
duff_CFLAGS = -Wall -Wextra -pedantic -std=c99 -I $(top_builddir)/lib @GLIB_CFLAGS@ @CJSON_CFLAGS@ -D_GNU_SOURCE
duff_LDADD = $(top_builddir)/lib/libduff.la @GLIB_LIBS@ @CJSON_LIBS@
