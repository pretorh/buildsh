#include "generator.h"
#include "utils.h"

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
        exit_failure_printf("error reading file %s\n", file);
    }

    char buffer[MAX_COMMAND_LENGTH];
    int size = fread(buffer, sizeof(char), MAX_COMMAND_LENGTH, fp);
    fclose(fp);

    if (size == MAX_COMMAND_LENGTH) {
        exit_failure_printf("file %s too large\n", file);
    }

    CONCAT_LINE(destination, buffer);
}

// helper generator functions

void generator_build_dir_setup(struct Settings *settings) {
    char current[MAX_COMMAND_LENGTH];
    strcpy(current, settings->build_dir_setup);

    settings->build_dir_setup[0] = 0;
    concat_formatted_string(settings->build_dir_setup, MAX_COMMAND_LENGTH,
        "%s%s",
        "\n"
        "BUILD_DIR=$(mktemp -d ./buildsh-build-XXXXX)\n"
        "cd $BUILD_DIR\n",
        current);
}

void generator_extract_source(struct Settings *settings) {
    char current[MAX_COMMAND_LENGTH];
    strcpy(current, settings->source_setup);

    settings->source_setup[0] = 0;
    concat_formatted_string(settings->source_setup, MAX_COMMAND_LENGTH,
        "tar xf %s\n"
        "cd %s\n"
        "%s",
        settings->archive, settings->name, current);
}

void generator_configure(struct Settings *settings) {
    APPLY_DEFAULT(settings->configure_commands,
        "%s%s/%s%s\n",
        settings->config_env, settings->config_dir, settings->config_script_name, settings->config_options);
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
    APPLY_DEFAULT(settings->config_script_name,
        "%s",
        "configure");

    generator_extract_source(settings);

    if (settings->build_outside_sources)
        generator_build_dir_setup(settings);
    if (settings->do_configure)
        generator_configure(settings);
    if (settings->do_build)
        generator_build(settings);
    if (settings->do_test)
        generator_test(settings);

    generator_install(settings);
    generator_cleanup(settings);
}
