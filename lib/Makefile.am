lib_LTLIBRARIES = libduff.la

libduff_la_SOURCES = cli.c \
					 duff.c \
					 io.c \
					 log.c \
					 mem.c \
					 package.c \
					 request.c \
					 response.c \
					 sync.c \
					 vector.c

include_HEADERS = cli.h \
				  duff.h \
				  io.h \
				  log.h \
				  mem.h \
				  package.h \
				  request.h \
				  response.h \
				  sync.h \
				  vector.h

libduff_la_CFLAGS = -Wall -Wextra -pedantic -std=c99
libduff_la_CFLAGS += @CURL_CFLAGS@ @CJSON_CFLAGS@ -D_GNU_SOURCE
libduff_la_LIBADD = @CURL_LIBS@ @CJSON_LIBS@

CLEANFILES = *~
