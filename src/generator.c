#include "generator.h"
#include <stdio.h>

#define EMPTY_LINE puts("");

void extract(const char *archive, const char *name) {
    printf("tar xf %s\n", archive);
    printf("cd %s\n", name);
    EMPTY_LINE
}

void make_build_dir() {
    printf("mkdir build\n");
    printf("cd build\n");
    EMPTY_LINE
}

void configure(int nested_dir) {
    printf("%s/configure\n",
        nested_dir ? ".." : ".");
    EMPTY_LINE
}

void cleanup(const char *dir_name, int nested_dir) {
    printf("cd ../%s\n", nested_dir ? "../" : "");
    printf("rm -rf %s\n", dir_name);
    EMPTY_LINE
}
