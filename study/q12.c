/*
[문제12] 정수의 짝, 홀 판별하기 (비트 clear 연산자(&))
비트clear 연산자(&)를 이용해 입력 받은 정수가 짝수인지 홀수인지 판별하는
프로그램을 작성하시오 나머지 연산자는 사용할 수 없다.

1) 실행결과 숫자 입력: 7
짝수: X
홀수: O
숫자 입력: 8
짝수: O
홀수: X

*/

#include <stdio.h>

int main(void) {

    int num;

    printf("숫자 입력 : ");
    fflush(stdout);
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "숫자를 입력하시오.");
        return 1;
    }

    // 연산 순위 & < == !!!
    if (num & 1) {
        printf("짝수: X\n홀수: O\n");
    } else {
        printf("짝수: O\n홀수: X\n");
    }

    return 0;
}
