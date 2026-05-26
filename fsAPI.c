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
    disk->inode_list[free_inode_index].used = 1; // 파일이 사용 중임을 표시

    return free_inode_index;
}
