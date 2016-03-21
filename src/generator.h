#ifndef _GENERATOR_H_
#define _GENERATOR_H_

void extract(const char *archive, const char *name);
void make_build_dir();
void configure(int nested_dir, const char *arguments);
void build(int max_jobs);
void install();
void cleanup(const char *dir_name, int nested_dir);
void run(const char *commands);

#endif
