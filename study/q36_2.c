/*
** 누적 재귀함수 버전

[문제36] 피보나치 수열은 첫 두 항이 1이고, 세 번째 항부터는 바로 앞 두 항의 합이 되는 수열로,
1, 1, 2, 3, 5, 8, 13... 순으로 나타난다.
피보나치 수열 제 10차항까지 나타내는 함수를 재귀함수로 작성하시오
1) 함수 prototype
𝐹𝑛=𝐹𝑛−1+𝐹𝑛−2
int fibonacci(int);

*/
#include <assert.h>
#include <stdio.h>

int fibonacci(int);
static int fib_step(int remaining, int a, int b);

int main(void) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", fibonacci(i));
    }
    printf("\n");

    return 0;
}

int fibonacci(int n) {
    // 조건이 거짓이면 프로그램 강제 종료. 사용자 입력 검증은 if
    assert(n >= 1);
    if (n <= 2) {
        return 1;
    }

    return fib_step(n - 2, 1, 1);
}

static int fib_step(int remaining, int a, int b) {
    if (remaining == 0) {
        return b;
    }
    return fib_step(remaining - 1, b, a + b);
}
