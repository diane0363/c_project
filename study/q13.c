/*
[문제13] 일수를 입력 받아 그 값을 주와 일수로 변환하는 프로그램 작성.
1) 실행 예
날수를 입력하시오 : 25
25일은 3주 4일입니다

*/

#include <stdio.h>

int main(void) {
    int days;

    printf("날수를 입력하시오 : ");
    fflush(stdout);
    if (scanf("%d", &days) != 1 || days < 0) {
        fprintf(stderr, "0이상의 정수를 입력하시오.\n");
        return 1;
    }

    int weeks = days / 7;
    int rest = days % 7;

    printf("%d일은 %d주 %d일입니다.\n", days, weeks, rest);
    return 0;
}
