#include "utils.h"
#include <stdarg.h>
#include <string.h>

void concat_formatted_string(char *into, int length, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int offset = strlen(into);
    int remain = length - offset;
    int written = vsnprintf(into + offset, remain, format, args);
    if (written < 0 || written > remain) {
        exit_failure_printf("overflow in string (%d+%d >= %d)\n", offset, written, length);
    }
    va_end(args);
}
