#include <stdio.h>
#include <virtual-disk.c>

/*
create_file은 디스크에 파일 이름만 할당시키고 내용은 전부 비우도록 하는 함수
*/
int create_file(virtualDisk *disk, char *name) {
    int free_inode_index = -1;
    
    for (int i = 0; i < MAX_FILES; i++) {
        // 힌트: disk 포인터에서 바로 inode_list[i]로 접근합니다.
        if (disk->inode_list[i].used == 0) { 
            free_inode_index = i;
            break;
        }
    }
    if(free_inode_index == -1) return -1;
    disk->inode_list[free_inode_index].used = 1; // 파일이 사용 중임을 표시

    return free_inode_index;
}

int find_free_block(virtualDisk *disk){
    for (int i = 0; i < TOTAL_BLOCKS ; i ++){
        if(disk -> block_bitmap[i] == 0) return i;
    }
    return -1;
}

/*
원하는 내용을 쓰고싶으면
가상 디스크에 원하는 inodeNumber에 쓴다...?
inodeNumber는 비어있는거? 아니지
해당하는 파일 즉 파일을 가리키고 있는 inodeNumber를 써야하지.
그럼 write file은 어떤 로직이 필요한건가?
data block에 data를 써야해
어떻게 쓰지?
data 블록 중에 비어있는 블록 찾아서 inode의 블록 리스트에 넣기

*/
int write_file(virtualDisk *disk, char *data, int iNodeNumber){
    Inode findInode = disk->inode_list[iNodeNumber];
    int block_idx = find_free_block(disk);
    
    if (block_idx == -1){
        printf("디스크에 남은 블록이 없습니다.");
        return -1;
    }
    
    disk -> block_bitmap[block_idx] = 1;
    // 저장할 inode의 블록idx 배열 idx 찾기
    // block_idx를 비어있는 inode의 블록에 넣기
    for(int i = 0; i< sizeof(disk -> inode_list[iNodeNumber].blocks) / sizeof(int) ; i++){
        if(disk -> inode_list[iNodeNumber].blocks[i] == -1){
            disk -> inode_list[iNodeNumber].blocks[i] = block_idx;
            break;
        }
    }

}


