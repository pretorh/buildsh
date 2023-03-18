#include "../generator.h"

void set_makeinstall_destdir(struct Settings *settings, const char *path) {
    CONCAT_PRINTF(settings->install_options, " DESTDIR=%s", path);
}

void add_install_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->install_commands, command);
}

void add_install_file(struct Settings *settings, const char *file) {
    concat_file(settings->install_commands, file);
}
