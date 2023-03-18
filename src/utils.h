#ifndef _BUILDSH_UTILS_H_
#define _BUILDSH_UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#define exit_failure_printf(format, ...) \
    fprintf(stderr, format, __VA_ARGS__); \
    exit(EXIT_FAILURE);
#define exit_failure_message(format) \
    fprintf(stderr, format); \
    exit(EXIT_FAILURE);

void concat_formatted_string(char *into, int length, const char *format, ...);

#endif
