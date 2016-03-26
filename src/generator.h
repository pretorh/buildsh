#ifndef _GENERATOR_H_
#define _GENERATOR_H_

void extract(const char *archive, const char *name);
void make_build_dir();
void configure(const char *dir, const char *env, const char *arguments);
void cleanup(const char *dir_name, int nested_dir);
int run(const char *commands);

#endif
