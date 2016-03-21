#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

struct Settings {
    const char *name;
};

void parse_settings(int argc, char *argv[], struct Settings *settings);
void parse_arguments(int argc, char *argv[], struct Settings *settings);
void parse_name_from_remaining(int argc, char *argv[], struct Settings *settings);

int main(int argc, char *argv[]) {
    struct Settings settings;
    parse_settings(argc, argv, &settings);

    extract(settings.name);

    return 0;
}

void parse_settings(int argc, char *argv[], struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
    parse_arguments(argc, argv, settings);
    parse_name_from_remaining(argc, argv, settings);
}

void parse_arguments(int argc, char *argv[], struct Settings *settings) {
    static const char short_options[] = "";
    static struct option long_options[] = {
        {0, 0, 0, 0}
    };

    int c, index;
    while ((c = getopt_long (argc, argv, short_options, long_options, &index)) != -1) {
        switch (c) {
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
