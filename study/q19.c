/*
[문제19] 알파벳을 입력하여 대소문자 바꾸기
키보드로 알파벳을 입력 받은 후 대문자는 소문자로
소문자는 대문자로 바꾸어 출력하시오
만약 입력된 값이 알파벳이 아닌 경우 "알파벳을 입력하시오"라는
문자열을 출력한 후 프로그램을 종료한다.
1) 실행 결과
알파벳 입력 : a
a -> A
알파벳 입력 : ?
알파벳을 입력하시오

*/

#include <ctype.h>
#include <stdio.h>

// A : 65 ~ 90, a : 97 ~ 122
int main(void) {
    char alp;

    printf("알파벳 입력 : ");
    fflush(stdout);
    if (scanf("%c", &alp) != 1 || !isalpha(alp)) {
        fprintf(stderr, "알파벳을 입력하시오.\n");
        return 1;
    }

    // 비트 변환 버전 (32 = 0x20)
    printf("%c -> %c\n", alp, alp ^ 0x20);

    return 0;
}
