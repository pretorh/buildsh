#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <limits.h>
#include <string.h>

#define APPLY_DEFAULT(field, format, ...) \
    if (*field == 0) \
        sprintf(field, format, __VA_ARGS__);

struct Settings {
    const char *name;
    char archive[PATH_MAX + 1];
    int build_outside_sources;
    int max_make_jobs;

    // commands
    char source_setup[8192];
    char configure_commands[8192];
    char build_commands[8192];
    char test_commands[8192];
    char install_commands[8192];
    char install_post[8192];
    char cleanup_commands[8192];

    // default action options
    char config_dir[PATH_MAX + 1];
    char config_env[8192];
    char config_options[8192];
    char make_options[8192];
    int install_sudo;

    // actions
    int do_configure;
    int do_build;
    int do_test;
};

int run(const char *commands);

void generator_init(struct Settings *settings);
void generator_finalize_setup(struct Settings *settings);

#endif
