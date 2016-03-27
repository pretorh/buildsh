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

int run(const char *commands) {
    if (*commands == 0)
        return 0;
    printf("%s\n", commands);
    return 1;
}

void generator_init(struct Settings *settings) {
    memset(settings, 0, sizeof(*settings));
    settings->max_make_jobs = 4;
    settings->do_configure = 1;
    settings->do_build = 1;
}

void generator_finalize_setup(struct Settings *settings) {
    APPLY_DEFAULT(settings->archive,
        "%s.tar.*",
        settings->name);
    APPLY_DEFAULT(settings->config_dir,
        "%s",
        ".");

    APPLY_DEFAULT(settings->configure_commands,
        "%s%s/configure%s\n",
        settings->config_env, settings->config_dir, settings->config_options);
    APPLY_DEFAULT(settings->build_commands,
        "make --jobs %d %s\n",
        settings->max_make_jobs, settings->make_options);
    APPLY_DEFAULT(settings->install_commands,
        "%s\n",
        "make install");
    APPLY_DEFAULT(settings->test_commands,
        "make check --jobs %d\n",
        settings->max_make_jobs);
    APPLY_DEFAULT(settings->cleanup_commands,
        "cd %s\n"
        "rm -rf %s\n",
        settings->build_outside_sources ? "../.." : "..",
        settings->name);
}
