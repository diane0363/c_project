/*
UAF (Use-After-Free)
- 댕글링 포인터 역참조 행위
- ダングリングポインタ : 수명이 끝난 메모리를 여전히 가리키고 있는 행위
- 위험한 이유
  - 반납된 블록 재사용 (현재 reuse 코드)
  - 할당된 메타데이터 오염
    - glibc 는 해제된 블록 내부에 다음 빈 블록을 가리키는 포인터 저장 -> UAF는 해당 연결 리스트 오염
    - 이 후의 malloc/free 에서 크래시 발생 가능성. 
  - 
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *a = malloc(sizeof *a);

    if (a == NULL) return 1; // 確保失敗チェック； 確保失敗しNULL帰る

    *a = 42; 

    printf("a 주소: %p\n", (void *)a);

    free(a);                        // a ； ダングリングポインタ ＆ まだ、同じアドレスを目指す

    // C표준은 malloc이 어떤 주소를 줄 지 약속 X
    // 하지만, glibc는 같은 크기의 블록을 tcache라는 LIFO(스택) 목록으로 관리 -> 반납된 칸이 위로 올라가고, 다음 요청에서 꺼낸다. 
    // 공격자가 UAF를 익스플로잇할 수 있는 이유.. 
    int *b = malloc(sizeof *b);     // 같은 크기 요청 → 같은 칸이 나올 가능성 높음
    if (b == NULL) return 1;
    *b = 999;
    printf("b 주소: %p\n", (void *)b);
    printf("b 값  : %d\n", *b);

    // 1. NULL 대입 X
    // *a = 7;                         // UAF: 반납한 열쇠로 남의 칸을 엶 (UB)
    
    // 2. NULL 대입 : 원인 위치에서 즉시 죽는 버그가 가장 좋은 버그. free한 변수는 NULL대입해주기
    a = NULL; // NULL은 0번지
    *a = 7; // 0번지에 쓰기 시도 -> Linux는 0번지를 매핑 X -> CPU가 접근하는 순간 OS가 프로세스를 SIGSEGV로 즉시 죽임.

    printf("a로 쓴 뒤 b 값: %d\n", *b);

    free(b);



    return 0;
}