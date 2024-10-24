#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/directories.h"
#include "include/files.h"
#include "include/inode.h"
#include "include/utils.h"

void *checked_malloc(int len);

char *uint32_to_str(uint32_t i);

void exit_program(){
    exit(EXIT_SUCCESS);
}