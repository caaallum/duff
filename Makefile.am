AUTOMAKE_OPTIONS = foreign
SUBDIRS = lib cli test

CLEANFILES = *~

cleandev:
	@rm -f compile-commands.json

dev:
	@compiledb -n $(MAKE)
