#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include <linux/limits.h>
#include <string.h>
#include <stdio.h>

#define MAX_COMMAND_LENGTH 8192

#define APPLY_DEFAULT(field, format, ...) \
    if (*field == 0) \
        concat_formatted_string(field, MAX_COMMAND_LENGTH, format, __VA_ARGS__);
#define CONCAT_PRINTF(field, format, ...) \
    concat_formatted_string(field, MAX_COMMAND_LENGTH, format, __VA_ARGS__)
#define CONCAT_LINE(field, line) \
    CONCAT_PRINTF(field, "%s\n", line)

struct Settings {
    const char *name;
    char archive[PATH_MAX + 1];
    int build_outside_sources;
    int max_make_jobs;

    // commands
    char source_setup[MAX_COMMAND_LENGTH];
    char build_dir_setup[MAX_COMMAND_LENGTH];
    char configure_commands[MAX_COMMAND_LENGTH];
    char build_commands[MAX_COMMAND_LENGTH];
    char test_commands[MAX_COMMAND_LENGTH];
    char install_commands[MAX_COMMAND_LENGTH];
    char install_post[MAX_COMMAND_LENGTH];
    char cleanup_commands[MAX_COMMAND_LENGTH];

    // default action options
    char config_dir[PATH_MAX + 1];
    char config_script_name[PATH_MAX + 1];
    char config_env[MAX_COMMAND_LENGTH];
    char config_options[MAX_COMMAND_LENGTH];
    char make_options[MAX_COMMAND_LENGTH];
    int install_sudo;
    char install_options[MAX_COMMAND_LENGTH];

    // actions
    int do_configure;
    int do_build;
    int do_test;
};

int run(const char *commands);
void concat_file(char *buffer, const char *file);

void generator_init(struct Settings *settings);
void generator_output_shell_commands(struct Settings *settings);
void generator_finalize_setup(struct Settings *settings);

void add_source_setup_command(struct Settings *settings, const char *command);
void add_source_setup_file(struct Settings *settings, const char *command);
void add_build_dir_setup_command(struct Settings *settings, const char *command);

void set_configure_dir(struct Settings *settings, const char *path);
void set_configure_script_name(struct Settings *settings, const char *path);
void add_configure_envvar(struct Settings *settings, const char *envvar);
void add_configure_option(struct Settings *settings, const char *option);
void add_configure_value(struct Settings *settings, const char *value);
void add_configure_command(struct Settings *settings, const char *command);
void add_configure_file(struct Settings *settings, const char *file);

void add_build_command(struct Settings *settings, const char *command);
void add_make_option(struct Settings *settings, const char *option);
void add_build_file(struct Settings *settings, const char *file);

void set_makeinstall_destdir(struct Settings *settings, const char *path);
void add_makeinstall_option(struct Settings *settings, const char *option);
void add_install_command(struct Settings *settings, const char *command);
void add_install_file(struct Settings *settings, const char *file);

void add_post_command(struct Settings *settings, const char *command);
void add_post_file(struct Settings *settings, const char *file);

#endif
