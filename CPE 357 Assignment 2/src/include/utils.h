#define UTILS_H

#include <stdint.h>

void *checked_malloc(int len);

char *uint32_to_str(uint32_t i);

void exit_program();