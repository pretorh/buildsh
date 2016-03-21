bin_PROGRAMS = buildsh
EXTRA_DIST = $(TESTS)

TESTS =
TESTS += tests/extract-sources.sh
TESTS += tests/extract-sources-from-archive.sh
TESTS += tests/build-dir.sh
TESTS += tests/configure.sh
TESTS += tests/configure-options.sh
TESTS += tests/build.sh
TESTS += tests/install.sh
TESTS += tests/cleanup.sh

buildsh_CFLAGS = -ggdb -pedantic -Wall -Wextra
buildsh_SOURCES = src/main.c
buildsh_SOURCES += src/generator.c
