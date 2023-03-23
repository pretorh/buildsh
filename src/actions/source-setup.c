#include "../generator.h"
#include "../utils.h"

void add_source_setup_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->source_setup, command);
}

void add_source_setup_file(struct Settings *settings, const char *file) {
    concat_file(settings->source_setup, file);
}

void add_build_dir_setup_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->build_dir_setup, command);
}
