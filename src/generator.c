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

void configure(int nested_dir, const char *arguments) {
    printf("%s/configure%s\n",
        nested_dir ? ".." : ".",
        arguments);
    EMPTY_LINE
}

void build(int max_jobs, const char *arguments) {
    printf("make --jobs %d %s\n", max_jobs, arguments);
    EMPTY_LINE
}

void install(const char *custom_commands) {
    if (run(custom_commands))
        return;

    printf("make install\n");
    EMPTY_LINE
}

void cleanup(const char *dir_name, int nested_dir) {
    printf("cd ../%s\n", nested_dir ? "../" : "");
    printf("rm -rf %s\n", dir_name);
    EMPTY_LINE
}

int run(const char *commands) {
    if (*commands == 0)
        return 0;
    printf("%s\n", commands);
    return 1;
}
