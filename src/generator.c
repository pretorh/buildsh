#include "generator.h"
#include <stdio.h>

void extract(const char *name) {
    printf("tar xf %s.tar.*\n", name);
    printf("cd %s\n", name);
}
