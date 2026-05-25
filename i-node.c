#define BLOCK_SIZE 4096
#define MAX_INODES 128
#define DIRECT_BLOCKS 10

typedef struct {
    int used; //0으로 초기화
    char name[32]; // 파일 이름
    int size; // 파일 사이즈
    int blocks[DIRECT_BLOCKS]; // inode 한개당 저장하는 
} Inode;