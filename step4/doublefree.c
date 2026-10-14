/*
Double Free
- 할당자가 같은 주소를 빈 목록에 두 번 넣으면서,같은 주소를 두 객체에 나눠줄 수도 있다. (서로를 덮어씀)
- glibc이 일부 감지를 해 abort하지만 모든 경우는 X (free(): double free detected in tache 2)
- 같은 블록을 가리키는 포인터가 여러 개일 때 주의 !!!!!!!!!!

방어 수단
1. free 직후 NULL 대입. -> 다른 변수를 쓰는 경우 한계
2. 소유권 규칙 정하기 (free할 책임이 있는 포인터 정하기. 나머지는 빌려 쓰는 포인터) 
3. AddressSanitizer (-fsanitize=address) 사용하기
  - 잘못된 접근 위치, free한 위치, malloc한 위치의 스택 트레이스 출력.
  - -g : 파일명과 줄번호 옵션
*/

// 1
int *p = malloc(sizeof *p);
free(p);
free(p);   // double free → UB 

// 2 같은 블록을 가리키는 포인터가 여러개일 때
char *a = malloc(16);
char *b = a;     // 같은 블록을 가리키는 포인터가 둘
free(a);
free(b);         // double free — 변수 이름이 달라서 눈에 잘 안 띔

char *a = malloc(16);
free(a);
char *b = malloc(16);     // b에게 할당
free(a);         // 해당 블록이 b에게 재할당된 이후라 glibc의 double free detected 검사에서도 대부분 통과..
