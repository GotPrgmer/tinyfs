# tiny file system implementation
## 구현 설계

### i-node를 i-node최대 보유 개수만큼 생성하고 데이터 블록의 차지 유무인 used를 0으로 초기화

## 1. super-block
### 블록의 개수
### 아이노드 개수

## 2. i-node
### used는 현재 data block이 할당됐는지 확인하는 필드
### used를 안쓰려면 data block이 할당되어있는지 현황을 파악하는
### 테이블이 있으면 됨.

## 3. fs 기능
### 3-1. create (파일 생성)
### 3-2. read (파일 읽기)
### 3-3. write (파일 쓰기)
### 3-4. rename (우선 필수 기능이 아니므로 배제)
