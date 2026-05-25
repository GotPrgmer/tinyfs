#define BLOCK_SIZE 1024
#define TOTAL_BLOCKS 32

// 실제 데이터가 저장될 가상 디스크(데이터 블록 구역)
char data_blocks[TOTAL_BLOCKS][BLOCK_SIZE];

