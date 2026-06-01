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

/*
파일은 어떻게 읽으면 될까?
인풋은 어떤게 들어오는 걸까?
inodeNumber는 들어와야할거같아.

*/
int read_file(virtualDisk *disk){

}

// 비트맵중에 비어있는 공간의 idx를 반환
int find_free_block(virtualDisk *disk){
    for (int i = 0; i < TOTAL_BLOCKS ; i ++){
        if(disk -> block_bitmap[i] == -1) return i;
    }
    return -1;
}

/**
 * @brief 가상 디스크의 특정 i-node에 데이터를 블록 단위로 저장합니다.
 * * @param disk 가상 디스크 구조체의 포인터
 * @param data 저장할 문자열 데이터
 * @param iNodeNumber 데이터를 저장할 대상 파일의 i-node 인덱스
 * @return int 성공 시 0, 오류(디스크 용량 초과 등) 발생 시 -1
 * * @details 
 * 1. 전달받은 i-node 번호를 통해 파일의 정보를 가져옵니다.
 * 2. 빈 데이터 블록을 찾아 비트맵을 업데이트하고 i-node의 블록 리스트에 연결합니다.
 * 3. 블록 크기 제한(1024자)을 체크한 뒤 데이터를 실제 블록 공간에 복사합니다.
 */
// 블록 단위로만 저장을 하도록 설계.
int write_file(virtualDisk *disk, char *data, int iNodeNumber){


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
    for(int i = 0; i< sizeof(disk -> inode_list[iNodeNumber].blocksIdx) / sizeof(int) ; i++){
        if(disk -> inode_list[iNodeNumber].blocksIdx[i] == -1){
            disk -> inode_list[iNodeNumber].blocksIdx[i] = block_idx;
            break;
        }
    }

    // 데이터 크기가 블록 크기보다 작다면 안전하게 복사
    if (strlen(data) < BLOCK_SIZE) {
        strncpy(disk->data_blocks[block_idx], data, BLOCK_SIZE);
    } else {
        printf("데이터가 블록 크기를 초과했습니다.\n");
        return -1;
    }

}

/**
 * @brief 가상 디스크의 특정 블록 공간에 데이터를 한 글자씩 검사하며 저장합니다.
 * @param disk 가상 디스크 구조체의 포인터
 * @param block_idx 데이터를 저장할 대상 물리 블록 인덱스
 * @param data 저장할 문자열 데이터
 * @return int 성공 시 0, 블록 공간 부족 시 -1
 */
int save_data_to_block(virtualDisk *disk, int block_idx, char *data) {
    int remainBlockStorage = 0;
    int availableSaveIdx = 0;
    
    // 1. 해당 블록의 사용 가능한 남은 공간 계산
    for(int i = 0; i < BLOCK_SIZE; i++) {
        if(disk->data_blocks[block_idx][i] != -1) {
            availableSaveIdx = i;
            remainBlockStorage = BLOCK_SIZE - (availableSaveIdx + 1);
            break;
        }
    }
    
    // 남은 공간이 넣으려는 데이터 크기보다 작으면 저장 실패
    if(remainBlockStorage < strlen(data)) {
        return -1;
    }
    
    // 2. 블록에 데이터 한 글자씩 복사
    for(int i = 0; i < strlen(data); i++) {
        disk->data_blocks[block_idx][i] = *(data + i);
    }
    
    // 문자열의 끝을 알리는 널(Null) 문자 삽입
    disk->data_blocks[block_idx][strlen(data)] = '\0';

    return 0;
}


