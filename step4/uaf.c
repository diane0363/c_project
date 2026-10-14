/*
과제 A. 컴파일하기 전에 이 코드의 버그를 모두 찾고, 각각이 댕글링 / UAF / 이중 해제 중 무엇인지 분류하십시오. (위 섹션 외의 문제가 있다면 그것도 지적하십시오.)

과제 B. gcc -Wall -Wextra -g -fsanitize=address uaf.c -o uaf로 컴파일하고 실행하십시오. 컴파일 경고와 ASan 출력을 붙여넣고, ASan이 첫 번째로 보고한 오류가 무엇인지, 그리고 왜 나머지 버그는 보고되지 않았는지 설명하십시오.

과제 C. 모든 버그를 고친 버전을 제출하십시오. 조건: make_name은 호출자가 해제하는 힙 문자열을 반환하도록 바꾸고, 그 소유권 계약을 함수 위 주석으로 명시할 것. ASan 출력이 깨끗해야 합니다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  const char *src;   // *src = 'a';  ❌ 컴파일 에러   src++;  ✅ 가능  
    ** Java에는 참조를 통해 객체 내용을 못 바꾸게하는 키워드 X -> String을 불변 클래스로 만든 이유
  char *const src;   // *src = 'a';  ✅ 가능          src++;  ❌ 컴파일 에러  
    ** Java의 final String s
*/
char *make_name(const char *src) { 
  /* 매개변수를 const로 지정? 
    => src를 통해 문자를 수정하지 않겠다는 의미. (문자열 리터럴은 수정하면 UB. 읽기전용 메모리에 있다.) 
    만약 char *src를 매개변수로 넣고 함수 내에서 src[0] = 'C'로 값 변경 시도 시 읽기 전용 영역에서 수정을 시도하기 때문에 SEGV로 죽음 (NULL 쓰기(0번지)와 동일)
    하지만 컴파일이 되기 때문에 (문자열 리터럴 타입은 char[]이다.) const char * 을 사용하는 것이 방어선
  */
    char buf[32];
    /* strcpy는 목적지의 크기를 전혀 모름. 
        => \0이 나올 때까지 그냥 깊은 복사.. 
        => src가 31글자를 넘으면 buf를 넘어 다른 데이터를 덮어쓰는 스택 버퍼 오버플로 사고 가능성!!!
        - const char *p = src; 얕은 복사(주소만)
    */
    strcpy(buf, src); 
    return buf; // ** 댕글링
}


int main(void) {
  /*
    - sizeof는 연산자. 식을 쓸 땐 괄호 필요 X ; sizeof *scores
    - 타입을 쓸 때만 괄호 필수 ; sizeof(int)
  */
    int *scores = malloc(3 * sizeof *scores); // 3 * sizeof *scores 이건 int이 3개 들어갈 만큼의 메모리 할당 맞지? sizeof를 그냥 저렇게 써도 되는 것임??
    if (scores == NULL) { // 메모리 할당 성공여부 체크 
        return 1;
    }
    scores[0] = 90;
    scores[1] = 80;
    scores[2] = 70;

    int *alias = scores; 
    free(scores); // alias, scores 모두 댕글링 

    printf("first score: %d\n", alias[0]); // UAF. 이미 해제한 메모리 사용

    char *name = make_name("chip8"); // 댕글링. 지역변수 buf 소멸 -> 리턴하는 쪽이 댕글링
    printf("name: %s\n", name); // UAF..가 아닌 stack-use-after-return 지역 변수 buf는 함수가 끝나면서 소멸되는데, name은 해당 buf를 가리키는 문제가 생김

    free(alias); // 이중 해제 
    return 0;
}


