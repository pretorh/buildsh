#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <linux/limits.h>
#include <string.h>
#include <stdio.h>

#define APPLY_DEFAULT(field, format, ...) \
    if (*field == 0) \
        sprintf(field, format, __VA_ARGS__);
#define eos(s) (s)+strlen(s)
#define CONCAT_PRINTF(field, format, ...) \
    sprintf(eos(field), format, __VA_ARGS__)
#define CONCAT_LINE(field, line) \
    CONCAT_PRINTF(field, "%s\n", line)

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
    char install_options[8192];

    // actions
    int do_configure;
    int do_build;
    int do_test;
};

int run(const char *commands);
void concat_file(const char *buffer, const char *file);

void generator_init(struct Settings *settings);
void generator_finalize_setup(struct Settings *settings);

void add_source_setup_command(struct Settings *settings, const char *command);
void add_source_setup_file(struct Settings *settings, const char *command);

void set_configure_dir(struct Settings *settings, const char *path);
void add_configure_envvar(struct Settings *settings, const char *envvar);
void add_configure_option(struct Settings *settings, const char *option);
void add_configure_value(struct Settings *settings, const char *value);
void add_configure_command(struct Settings *settings, const char *command);
void add_configure_file(struct Settings *settings, const char *file);

void add_build_command(struct Settings *settings, const char *command);
void add_make_option(struct Settings *settings, const char *option);
void add_build_file(struct Settings *settings, const char *file);

void set_makeinstall_destdir(struct Settings *settings, const char *path);
void add_install_command(struct Settings *settings, const char *command);
void add_install_file(struct Settings *settings, const char *file);

void add_post_command(struct Settings *settings, const char *command);
void add_post_file(struct Settings *settings, const char *file);

#endif
