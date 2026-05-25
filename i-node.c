#define BLOCK_SIZE 4096
#define MAX_INODES 128
#define DIRECT_BLOCKS 10

typedef struct {
    int used; //0으로 초기화
    char name[32]; // 파일 이름
    int size; // 파일 사이즈
    int blocks[DIRECT_BLOCKS];
} Inode;

// file system
/*
create
read
write
*/


//메모리

/*
초기
000000000000000000
000000000000000000
*/

/*
변경
100000000000000000
000000000000000000
*/

/*
변경
000000000000000000
000000000000000000
*/

/*
테이블을 만들던가, i-node가 들어간 주소의 파일
비트맵형식으로 만들고 비트맵과 i-node used랑 어떤관련?

i-node에 used가 필요한가?
used는 왜 필요한데
현재 쓰고있는지 아닌지 표시
그걸 표시해서 뭐할건데
테이블이나 비트맵형식의 업데이트를 그때그때 하도록
아니면 i-node자체가 없으면 0으로 생각하면안되나?
왜 테이블이 없으면 used가 있어야하는가?
테이블이 없으면 i-node가 있는 것들만 브루트포스로 체크하면되지않나?
i-node를 삭제하면안되냐
i-node를 삭제하는게 어떤의미냐?
i-node를 어떻게 삭제할거냐
아 그러면 used가 삭제의 의미
초기화를 했을때 i-node를 저장할 수 있는 파일의 갯수로
생성해줘야함.
*/