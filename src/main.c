#include "generator.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_version();
void parse_settings(int argc, char *argv[], struct Settings *settings);
void parse_env_var(struct Settings *settings);
void parse_arguments(int argc, char *argv[], struct Settings *settings);
void parse_name_from_remaining(int argc, char *argv[], struct Settings *settings);
void parse_flag_set(const char *name, const char *value, struct Settings *settings);
void parse_long_option(const char *name, const char *value, struct Settings *settings);

int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp("--version", argv[1]) == 0 || strcmp("-v", argv[1]) == 0)) {
        print_version();
        exit(EXIT_SUCCESS);
    }

    struct Settings settings;
    parse_settings(argc, argv, &settings);

    run(settings.source_setup);
    run(settings.configure_commands);
    run(settings.build_commands);
    run(settings.test_commands);
    run(settings.install_commands);
    run(settings.install_post);
    run(settings.cleanup_commands);

    return 0;
}

void print_version() {
    printf("%s\n", PACKAGE_STRING);
}

void parse_settings(int argc, char *argv[], struct Settings *settings) {
    generator_init(settings);

    parse_env_var(settings);
    parse_arguments(argc, argv, settings);
    parse_name_from_remaining(argc, argv, settings);

    generator_finalize_setup(settings);
}

void parse_env_var(struct Settings *settings) {
    char *value;

    if ((value = getenv("DESTDIR")))
        set_makeinstall_destdir(settings, value);
}

void parse_arguments(int argc, char *argv[], struct Settings *settings) {
    const char short_options[] = "";
    struct option long_options[] = {
        {"archive",                 required_argument, 0, 'a'},
        {"build-outside-sources",   no_argument      , &settings->build_outside_sources, 1},
        {"build-using",             required_argument, 0, 0},
        {"no-build",                no_argument     , &settings->do_build, 0},
        {"no-configure",            no_argument     , &settings->do_configure, 0},
        {"configure-dir",           required_argument, 0, 0},
        {"configure-env",           required_argument, 0, 0},
        {"configure",               required_argument, 0, 0},
        {"configure-val",           required_argument, 0, 0},
        {"configure-using",         required_argument, 0, 0},
        {"install-using",           required_argument, 0, 0},
        {"make",                    required_argument, 0, 0},
        {"max-jobs",                required_argument, 0, 0},
        {"post",                    required_argument, 0, 0},
        {"source-setup",            required_argument, 0, 0},
        {"sudo",                    no_argument      , &settings->install_sudo, 1},
        {"test",                    optional_argument, &settings->do_test, 1},
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
                    parse_flag_set(long_options[index].name, optarg, settings);
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

void parse_flag_set(const char *name, const char *value, struct Settings *settings) {
    if (strcmp("build-outside-sources", name) == 0 && *settings->config_dir == 0) {
        strcpy(settings->config_dir, "..");
    } else if (strcmp("test", name) == 0 && value) {
        strcat(settings->test_commands, value);
        strcat(settings->test_commands, "\n");
    }
}

void parse_long_option(const char *name, const char *value, struct Settings *settings) {
    if (strcmp("build-using", name) == 0) {
        add_build_command(settings, value);
    } else if (strcmp("configure-dir", name) == 0) {
        set_configure_dir(settings, value);
    } else if (strcmp("configure-env", name) == 0) {
        add_configure_envvar(settings, value);
    } else if (strcmp("configure", name) == 0) {
        add_configure_option(settings, value);
    } else if (strcmp("configure-val", name) == 0) {
        add_configure_value(settings, value);
    } else if (strcmp("configure-using", name) == 0) {
        add_configure_command(settings, value);
    } else if (strcmp("install-using", name) == 0) {
        add_install_command(settings, value);
    } else if (strcmp("make", name) == 0) {
        add_make_option(settings, value);
    } else if (strcmp("max-jobs", name) == 0) {
        settings->max_make_jobs = atoi(value);
    } else if (strcmp("post", name) == 0) {
        add_post_command(settings, value);
    } else if (strcmp("source-setup", name) == 0) {
        add_source_setup_command(settings, value);
    } else {
        fprintf(stderr, "long option not implemented: %s\n", name);
        exit(EXIT_FAILURE);
    }
}
