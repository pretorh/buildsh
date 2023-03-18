#include "../generator.h"

void set_configure_dir(struct Settings *settings, const char *path) {
    strcpy(settings->config_dir, path);
}

void add_configure_envvar(struct Settings *settings, const char *envvar) {
    CONCAT_PRINTF(settings->config_env, "%s ", envvar);
}

void add_configure_option(struct Settings *settings, const char *option) {
    CONCAT_PRINTF(settings->config_options, " \\\n  --%s", option);
}

void add_configure_value(struct Settings *settings, const char *value) {
    CONCAT_PRINTF(settings->config_options, " \\\n  %s", value);
}

void add_configure_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->configure_commands, command);
}

void add_configure_file(struct Settings *settings, const char *file) {
    concat_file(settings->configure_commands, file);
}
