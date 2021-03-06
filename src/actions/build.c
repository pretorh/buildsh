#include "../generator.h"

void add_build_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->build_commands, command);
}

void add_make_option(struct Settings *settings, const char *option) {
    CONCAT_PRINTF(settings->make_options, " %s", option);
}
