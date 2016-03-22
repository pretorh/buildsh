bin_PROGRAMS = buildsh
EXTRA_DIST = $(TESTS)

TESTS =
TESTS += tests/extract-sources.sh
TESTS += tests/extract-sources-from-archive.sh
TESTS += tests/source-setup.sh
TESTS += tests/build-dir.sh
TESTS += tests/configure.sh
TESTS += tests/configure-options.sh
TESTS += tests/configure-dir.sh
TESTS += tests/configure-env.sh
TESTS += tests/build.sh
TESTS += tests/build-max-jobs.sh
TESTS += tests/build-options.sh
TESTS += tests/build-custom.sh
TESTS += tests/test-off-by-default.sh
TESTS += tests/test.sh
TESTS += tests/test-custom.sh
TESTS += tests/install.sh
TESTS += tests/install-custom.sh
TESTS += tests/post-install.sh
TESTS += tests/cleanup.sh

buildsh_CFLAGS = -ggdb -pedantic -Wall -Wextra
buildsh_SOURCES = src/main.c
buildsh_SOURCES += src/generator.c
