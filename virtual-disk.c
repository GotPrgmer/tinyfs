#include <super-block.c>
#define BLOCK_SIZE 1024
#define TOTAL_BLOCKS 32
#define MAX_FILES 16


typedef struct {
    superBlock super_block;
    char data_blocks[TOTAL_BLOCKS][BLOCK_SIZE];
    Inode inode_list[MAX_FILES];
    int block_bitmap[TOTAL_BLOCKS];
} virtualDisk;

