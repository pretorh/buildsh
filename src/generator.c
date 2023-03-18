#include "generator.h"
#include <stdlib.h>

#define EMPTY_LINE puts("");

int run(const char *commands) {
    if (*commands == 0)
        return 0;
    printf("%s\n", commands);
    return 1;
}

void concat_file(char *destination, const char *file) {
    FILE *fp = fopen(file, "r");
    if (fp == 0) {
        fprintf(stderr, "error reading file %s\n", file);
        exit(EXIT_FAILURE);
    }

    char buffer[8192];
    int size = fread(buffer, sizeof(char), 8192, fp);
    fclose(fp);

    if (size == 8192) {
        fprintf(stderr, "file %s too large\n", file);
        exit(EXIT_FAILURE);
    }

    CONCAT_LINE(destination, buffer);
}

// helper generator functions

void generator_create_build_dir(char *commands) {
    strcat(commands,
        "\n"
        "BUILD_DIR=$(mktemp -d ./buildsh-build-XXXXX)\n"
        "cd $BUILD_DIR\n");
}

void generator_extract_source(struct Settings *settings) {
    char current[8192];
    strcpy(current, settings->source_setup);

    sprintf(settings->source_setup,
        "tar xf %s\n"
        "cd %s\n"
        "%s",
        settings->archive, settings->name, current);
}

void generator_configure(struct Settings *settings) {
    APPLY_DEFAULT(settings->configure_commands,
        "%s%s/configure%s\n",
        settings->config_env, settings->config_dir, settings->config_options);
}

void generator_build(struct Settings *settings) {
    APPLY_DEFAULT(settings->build_commands,
        "make --jobs %d %s\n",
        settings->max_make_jobs, settings->make_options);
}

void generator_test(struct Settings *settings) {
    APPLY_DEFAULT(settings->test_commands,
        "make check --jobs %d\n",
        settings->max_make_jobs);
}

void generator_install(struct Settings *settings) {
    APPLY_DEFAULT(settings->install_commands,
        "%smake%s install\n",
        settings->install_sudo ? "sudo " : "",
        settings->install_options);
}

void generator_cleanup(struct Settings *settings) {
    APPLY_DEFAULT(settings->cleanup_commands,
        "cd %s\n"
        "rm -rf %s\n",
        settings->build_outside_sources ? "../.." : "..",
        settings->name);
}

// public generator functions

void generator_init(struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
    settings->max_make_jobs = 4;
    settings->do_configure = 1;
    settings->do_build = 1;
}

void generator_finalize_setup(struct Settings *settings) {
    APPLY_DEFAULT(settings->archive,
        "%s.tar.*",
        settings->name);
    APPLY_DEFAULT(settings->config_dir,
        "%s",
        ".");

    generator_extract_source(settings);

    if (settings->build_outside_sources)
        generator_create_build_dir(settings->source_setup);
    if (settings->do_configure)
        generator_configure(settings);
    if (settings->do_build)
        generator_build(settings);
    if (settings->do_test)
        generator_test(settings);

    generator_install(settings);
    generator_cleanup(settings);
}
