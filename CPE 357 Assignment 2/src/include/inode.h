#define INODE_H

#include <stdint.h>

/*typedef struct inode{
        uint32_t num;
        char type;
    };
*/

int validate_inode_num(int *num);

void save_inode_list(const char *dir);
