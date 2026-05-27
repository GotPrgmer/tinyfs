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

// 비트맵중에 비어있는 공간의 idx를 반환
int find_free_block(virtualDisk *disk){
    for (int i = 0; i < TOTAL_BLOCKS ; i ++){
        if(disk -> block_bitmap[i] == -1) return i;
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
// 블록 단위로만 저장을 하도록 설계.
int write_file(virtualDisk *disk, char *data, int iNodeNumber){

    // virtual disk의 블록 리스트에 data 넣기
    // data가 블록사이즈 보다 작은지 확인


    // iNodeNumber에 할당된 inode찾기
    Inode findInode = disk->inode_list[iNodeNumber];
    // virtual disk에서 비어있는 블록의 idx 찾기
    int block_idx = find_free_block(disk);
    if (block_idx == -1){
        printf("디스크에 남은 블록이 없습니다.");
        return -1;
    }
    
    // 비트맵에 해당 블록 idx를 사용중으로 바꾸기.
    disk -> block_bitmap[block_idx] = 1;
    // 저장할 inode의 블록idx 배열 idx 찾기
    // block_idx를 비어있는 inode에 연결된 블록에 넣기
    for(int i = 0; i< sizeof(disk -> inode_list[iNodeNumber].blocks) / sizeof(int) ; i++){
        if(disk -> inode_list[iNodeNumber].blocks[i] == -1){
            disk -> inode_list[iNodeNumber].blocks[i] = block_idx;
            break;
        }
    }

    // // virtual disk에 data 저장하기
    // int remainBlockStorage = 0;
    // int availableSaveIdx = 0;
    // for(int i=0; i<BLOCK_SIZE ; i++){
    //     if(disk->data_blocks[block_idx][i] != -1){
    //         availableSaveIdx = i;
    //         remainBlockStorage = BLOCK_SIZE - (availableSaveIdx+1);
    //         break;
    //     }
    // }
    // if(remainBlockStorage < strlen(data)) return -1;
    
    // // block storage에 하나씩 data 넣기
    // for(int i=0 ; i<strlen(data) ; i++){
    //     disk->data_blocks[block_idx][i] = *(data+i);
    // }
    // disk->data_blocks[block_idx][strlen(data)] = '\0';

    // 데이터 크기가 블록 크기보다 작다면 안전하게 복사
    if (strlen(data) < BLOCK_SIZE) {
        strncpy(disk->data_blocks[block_idx], data, BLOCK_SIZE);
    } else {
        printf("데이터가 블록 크기를 초과했습니다.\n");
        return -1;
    }

}


