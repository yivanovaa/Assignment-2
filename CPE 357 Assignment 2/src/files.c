#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/directories.h"
#include "include/files.h"
#include "include/inode.h"
#include "include/utils.h"

void load_inodes_list(const char *dir);

void create_file(const char *new_file);