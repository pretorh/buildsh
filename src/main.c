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
    int build_outside_sources;
};

void parse_settings(int argc, char *argv[], struct Settings *settings);
void parse_arguments(int argc, char *argv[], struct Settings *settings);
void parse_name_from_remaining(int argc, char *argv[], struct Settings *settings);

int main(int argc, char *argv[]) {
    struct Settings settings;
    parse_settings(argc, argv, &settings);

    extract(settings.archive, settings.name);
    if (settings.build_outside_sources)
        make_build_dir();
    cleanup(settings.name);

    return 0;
}

void parse_settings(int argc, char *argv[], struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
    parse_arguments(argc, argv, settings);
    parse_name_from_remaining(argc, argv, settings);

    APPLY_DEFAULT(settings->archive, "%s.tar.*", settings->name);
}

void parse_arguments(int argc, char *argv[], struct Settings *settings) {
    const char short_options[] = "";
    struct option long_options[] = {
        {"archive",                 required_argument, 0, 'a'},
        {"build-outside-sources",   no_argument      , &settings->build_outside_sources, 1},
        {0, 0, 0, 0}
    };

    int c, index;
    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
            case 'a':
                strncpy(settings->archive, optarg, PATH_MAX);
                break;

            case 0:
                if (long_options[index].flag != 0)
                    break; // flag set

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
