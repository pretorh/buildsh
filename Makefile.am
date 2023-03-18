bin_PROGRAMS = buildsh
EXTRA_DIST = src/utils.h $(TESTS) tests/setup.sh

TESTS =

TESTS += tests/extract/extract-and-cd.sh
TESTS += tests/extract/custom-archive-name.sh

TESTS += tests/source-setup/run-commands.sh
TESTS += tests/source-setup/build-dir.sh
TESTS += tests/source-setup/from-file.sh
TESTS += tests/source-setup/overflow-errors.sh

TESTS += tests/configure/default-configure.sh
TESTS += tests/configure/disabled.sh
TESTS += tests/configure/options.sh
TESTS += tests/configure/in-custom-dir.sh
TESTS += tests/configure/prefix-env.sh
TESTS += tests/configure/custom-commands.sh
TESTS += tests/configure/from-file.sh
TESTS += tests/configure/overflow-errors.sh

TESTS += tests/build/default-make.sh
TESTS += tests/build/disabled.sh
TESTS += tests/build/make-max-jobs.sh
TESTS += tests/build/make-targets.sh
TESTS += tests/build/custom-commands.sh
TESTS += tests/build/from-file.sh

TESTS += tests/test/default-off.sh
TESTS += tests/test/default-make-check.sh
TESTS += tests/test/custom.sh
TESTS += tests/test/from-file.sh

TESTS += tests/install/default-make-install.sh
TESTS += tests/install/destdir.sh
TESTS += tests/install/sudo.sh
TESTS += tests/install/custom.sh
TESTS += tests/install/from-file.sh

TESTS += tests/post/post-install.sh
TESTS += tests/post/cleanup.sh
TESTS += tests/post/from-file.sh
TESTS += tests/post/from-file-error-handling.sh

buildsh_CFLAGS = -ggdb -pedantic -Wall -Wextra
buildsh_SOURCES = src/main.c
buildsh_SOURCES += src/utils.c
buildsh_SOURCES += src/generator.c src/generator.h
buildsh_SOURCES += src/actions/source-setup.c
buildsh_SOURCES += src/actions/configure.c
buildsh_SOURCES += src/actions/build.c
buildsh_SOURCES += src/actions/install.c
buildsh_SOURCES += src/actions/post.c
