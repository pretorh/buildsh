#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <limits.h>

#define APPLY_DEFAULT(field, format, ...) \
    if (*field == 0) \
        sprintf(field, format, __VA_ARGS__);

struct Settings {
    const char *name;
    char archive[PATH_MAX + 1];

    char source_setup[8192];
    char config_dir[PATH_MAX + 1];
    char config_env[8192];
    char config_options[8192];
    char make_options[8192];
    char build_commands[8192];
    char install_commands[8192];
    char install_post[8192];

    int build_outside_sources;
    int max_make_jobs;
    int do_test;
};

void parse_settings(int argc, char *argv[], struct Settings *settings);
void parse_arguments(int argc, char *argv[], struct Settings *settings);
void parse_name_from_remaining(int argc, char *argv[], struct Settings *settings);
void parse_flag_set(const char *name, struct Settings *settings);
void parse_long_option(const char *name, const char *value, struct Settings *settings);

int main(int argc, char *argv[]) {
    struct Settings settings;
    parse_settings(argc, argv, &settings);

    extract(settings.archive, settings.name);
    run(settings.source_setup);
    if (settings.build_outside_sources)
        make_build_dir();
    configure(settings.config_dir, settings.config_env, settings.config_options);
    build(settings.max_make_jobs, settings.make_options, settings.build_commands);
    if (settings.do_test)
        run("make check\n");
    install(settings.install_commands);
    run(settings.install_post);
    cleanup(settings.name, settings.build_outside_sources);

    return 0;
}

void parse_settings(int argc, char *argv[], struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
    settings->max_make_jobs = 4;

    parse_arguments(argc, argv, settings);
    parse_name_from_remaining(argc, argv, settings);

    APPLY_DEFAULT(settings->archive, "%s.tar.*", settings->name);
    APPLY_DEFAULT(settings->config_dir, "%s", ".");
}

void parse_arguments(int argc, char *argv[], struct Settings *settings) {
    const char short_options[] = "";
    struct option long_options[] = {
        {"archive",                 required_argument, 0, 'a'},
        {"build-outside-sources",   no_argument      , &settings->build_outside_sources, 1},
        {"build-using",             required_argument, 0, 0},
        {"config-dir",              required_argument, 0, 0},
        {"config-env",              required_argument, 0, 0},
        {"config-opt",              required_argument, 0, 0},
        {"config-val",              required_argument, 0, 0},
        {"install-using",           required_argument, 0, 0},
        {"make",                    required_argument, 0, 0},
        {"max-jobs",                required_argument, 0, 0},
        {"post",                    required_argument, 0, 0},
        {"source-setup",            required_argument, 0, 0},
        {"test",                    no_argument      , &settings->do_test, 1},
        {0, 0, 0, 0}
    };

    int c, index;
    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
            case 'a':
                strncpy(settings->archive, optarg, PATH_MAX);
                break;

            case 0:
                if (long_options[index].flag != 0) {
                    parse_flag_set(long_options[index].name, settings);
                    break;
                }

                parse_long_option(long_options[index].name, optarg, settings);
                break;

            case '?':
            default:
                exit(EXIT_FAILURE);
        }
    }
}

void parse_name_from_remaining(int argc, char *argv[], struct Settings *settings) {
    if (argc - optind != 1) {
        fprintf(stderr, "Need exactly 1 non flag option\n");
        exit(EXIT_FAILURE);
    }
    settings->name = argv[optind];
}

void parse_flag_set(const char *name, struct Settings *settings) {
    if (strcmp("build-outside-sources", name) == 0 && *settings->config_dir == 0) {
        strcpy(settings->config_dir, "..");
    }
}

void parse_long_option(const char *name, const char *value, struct Settings *settings) {
    if (strcmp("build-using", name) == 0) {
        strcat(settings->build_commands, value);
        strcat(settings->build_commands, "\n");
    } else if (strcmp("config-dir", name) == 0) {
        strcpy(settings->config_dir, value);
    } else if (strcmp("config-env", name) == 0) {
        strcat(settings->config_env, value);
        strcat(settings->config_env, " ");
    } else if (strcmp("config-opt", name) == 0) {
        strcat(settings->config_options, " --");
        strcat(settings->config_options, value);
    } else if (strcmp("config-val", name) == 0) {
        strcat(settings->config_options, " ");
        strcat(settings->config_options, value);
    } else if (strcmp("install-using", name) == 0) {
        strcat(settings->install_commands, value);
        strcat(settings->install_commands, "\n");
    } else if (strcmp("make", name) == 0) {
        strcat(settings->make_options, " ");
        strcat(settings->make_options, value);
    } else if (strcmp("max-jobs", name) == 0) {
        settings->max_make_jobs = atoi(value);
    } else if (strcmp("post", name) == 0) {
        strcat(settings->install_post, value);
        strcat(settings->install_post, "\n");
    } else if (strcmp("source-setup", name) == 0) {
        strcat(settings->source_setup, value);
        strcat(settings->source_setup, "\n");
    } else {
        fprintf(stderr, "long option not implemented: %s\n", name);
        exit(EXIT_FAILURE);
    }
}
