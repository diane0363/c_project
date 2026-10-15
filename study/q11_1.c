/*
[문제11] 공배수 여부 출력하기
값을 3개 입력 받아 입력 받은 첫번째 수가 두 번째, 세번째 수의 공배수인지의
여부를 출력하시오 1) 실행 결과 정수 입력 : 18 첫 번째 정수 입력 : 3 두 번째 정수
입력 : 4 18은(는) 3과4의 공배수가 아닙니다. 정수 입력 : 12 첫 번째 정수 입력 : 3
두 번째 정수 입력 : 4
12은(는) 3과4의 공배수입니다.

*/

#include <stdio.h>

int main(void) {
    int n1, n2, n3;
    int common;

    printf("정수 입력 : ");
    fflush(stdout);
    if (scanf("%d", &n1) != 1) {
        fprintf(stderr, "0이상 정수 입력");
        return 1;
    }

    printf("첫 번째 정수 입력 : ");
    fflush(stdout);
    if (scanf("%d", &n2) != 1 || n2 < 1) {
        fprintf(stderr, "1이상 정수 입력");
        return 1;
    }

    printf("두 번째 정수 입력 : ");
    fflush(stdout);
    if (scanf("%d", &n3) != 1 || n3 < 1) {
        fprintf(stderr, "1이상 정수 입력");
        return 1;
    }

    common = (n1 % n2 == 0) && (n1 % n3 == 0);

    printf("%d은(는) %d과%d의 공배수%s\n", n1, n2, n3,
           common ? "입니다." : "가 아닙니다.");

    return 0;
}
