#include "generator.h"
#include <stdio.h>

void extract(const char *archive, const char *name) {
    printf("tar xf %s\n", archive);
    printf("cd %s\n", name);
}
