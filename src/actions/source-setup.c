#include "../generator.h"

void add_source_setup_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->source_setup, command);
}
