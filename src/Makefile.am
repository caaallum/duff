bin_PROGRAMS = duff

duff_SOURCES = duff.c \
			   args.c \
			   package.c \
			   str.c \
			   vector.c 

duff_CFLAGS = -Wall -Wextra -pedantic -std=c99 @CJSON_CFLAGS@ @CURL_CFLAGS@ @GLIB_CFLAGS@
duff_LDADD = @CJSON_LIBS@ @CURL_LIBS@ @GLIB_LIBS@

CLEANFILES = *~
