TESTCFLAGS = @CHECK_CFLAGS@ -I $(top_builddir)/lib @CJSON_CFLAGS@
TESTLDFLAGS = @CHECK_LIBS@ $(top_builddir)/lib/libduff.la @CJSON_LIBS@

check_PROGRAMS = api cli package #args

api_SOURCES = check_api.c
api_LDFLAGS = $(TESTLDFLAGS)
api_CFLAGS = $(TESTCFLAGS)

#args_SOURCES = check_args.c
#args_LDFLAGS = $(TESTLDFLAGS)
#args_CFLAGS = $(TESTCFLAGS)

cli_SOURCES = check_cli.c
cli_LDFLAGS = $(TESTLDFLAGS)
cli_CFLAGS = $(TESTCFLAGS)

package_SOURCES = check_package.c
package_LDFLAGS = $(TESTLDFLAGS)
package_CFLAGS = $(TESTCFLAGS)

TESTS = api cli package #args

CLEANFILES = *~
