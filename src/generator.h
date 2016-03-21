#ifndef _GENERATOR_H_
#define _GENERATOR_H_

void extract(const char *archive, const char *name);
void make_build_dir();
void configure(int nested_dir);
void cleanup(const char *dir_name, int nested_dir);

#endif
