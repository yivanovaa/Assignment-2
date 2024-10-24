#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include <stdint.h>

int validate_dir(const char *dir_name);

void load_root_dir(const char *dir);

void list_dir_contents(const char *dir);

void create_dir(const char *location, const char *new_dir_name);

void change_dir(const char *specified_dir);

void list_contents(const char *current_dir);

#endif

