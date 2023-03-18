#include "../generator.h"
#include "../utils.h"

void add_post_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->install_post, command);
}

void add_post_file(struct Settings *settings, const char *file) {
    concat_file(settings->install_post, file);
}
