#include "generator.h"
#include <stdio.h>

void extract(const char *archive, const char *name) {
    printf("tar xf %s\n", archive);
    printf("cd %s\n", name);
}

void cleanup(const char *dir_name) {
    printf("cd ..\n");
    printf("rm -rf %s\n", dir_name);
}
