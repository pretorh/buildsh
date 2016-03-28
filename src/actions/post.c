#include "../generator.h"

void add_post_command(struct Settings *settings, const char *command) {
    CONCAT_LINE(settings->install_post, command);
}
