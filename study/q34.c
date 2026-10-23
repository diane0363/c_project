/*
[문제34] 입력한 정수까지 존재하는 모든 소수 구하기 (함수 사용)
정수를 입력 받아 해당 정수까지 존재하는 모든 소수를 출력하고 소수의 개수가 몇 개인지 출력하는 코드를 작성하시오
1) 주의
숫자 2도 소수이므로 2를 입력했을 때에도 처리해야 한다.
2) 실행 결과
정수 입력: 2
2
2~2까지 소수의 개수는 1개입니다
정수 입력: 11
2 3 5 7 11
2~11까지 소수의 개수는 5개입니다
*/
#include <stdbool.h>
#include <stdio.h>

bool is_prime(int num);

int main(void) {
    int num;

    printf("정수 입력: ");
    fflush(stdout);
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "정수만 입력하시오.\n");
        return 1;
    }

    int count = 0;
    for (int i = 2; i <= num; i++) {
        if (is_prime(i)) {
            count++;
            printf("%d\t", i);
        }
    }
    printf("\n");
    printf("2~%d까지 소수의 개수는 %d개입니다\n", num, count);

    return 0;
}

// 소수 판단
bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i <= num / i; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
