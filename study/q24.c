/*
[문제24] 정수를 입력받아 해당 정수가 소수인지 판단하는 코드를 작성하시오
1)실행 예
정수 입력:2
2는 소수입니다.
정수 입력:4
4는 소수가 아닙니다.
*/
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int num;
    bool prime = true;

    printf("정수 입력:");
    fflush(stdout);
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "숫자를 입력하세요.\n");
        return 1;
    }

    // 1과 자신 사이의 수로 모두 나눠보기
    for (int n = 2; n < num; n++) {
        if (num % n == 0) {
            printf("%d는 소수가 아닙니다.\n", num);
            prime = false;
            break;
        }
    }

    // 나누어떨어지는게 없다면 소수
    if (prime) {
        printf("%d는 소수입니다.\n", num);
    }
}
