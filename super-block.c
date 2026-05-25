#include <i-node.c>
#define INODE_NUMBER
#define MAX_FILES 16

typedef struct
{

    int BLOCK_NUMBER;
    int INODE_NUMBER;
    Inode inode_list[MAX_FILES];

}superBlock;
