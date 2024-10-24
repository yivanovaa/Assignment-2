#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/files.h"
#include "include/inode.h"
#include "include/utils.h"
#include "include/directories.h"

int validate_dir(const char *dir_name);

void load_root_dir(const char *dir);

void list_dir_contents(const char *dir);

void create_dir(const char *location, const char *new_dir_name);

void change_dir(const char *specified_dir){
    if (chdir(specified_dir) != 0) {
        perror("Couldn't change dir.");
        exit(EXIT_FAILURE);
    }
};

void list_contents(const char *current_dir);

