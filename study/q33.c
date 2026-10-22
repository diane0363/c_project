/*
[문제33] 누승 함수 만들기
정수값을 n승하는 함수와 실수값을 n승하는 함수를 작성하시오. (반환값은 n승의 결과)
(단, 0의 어떤 승도 0이고, 어떤 수의 0승은 항상 1이 된다)
실수의 n승을 하는 함수의 출력 결과는 소수 2자리까지 출력
1) 함수 prototype
double fpow(double, int);
int ipow(int, int);
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h> // exit()

double fpow(double, int);
int ipow(int, int);

int main(void) {
    int n = 2;
    int n1 = 3;
    double n2 = 1.1;

    int result1 = ipow(n1, n);
    double result2 = fpow(n2, n);

    printf("ipow 결과 : %d ^ %d = %d\n", n1, n, result1);
    printf("fpow 결과 : %.2f ^ %d = %.2f\n", n2, n, result2);

    return 0;
}

double fpow(double base, int exp) {
    double result = 1;

    for (int i = 0; i < exp; i++) {
        result *= base;
    }

    return result;
}

/*
 * 빠른 거듭제곱: 지수를 이진수로 분해해 곱셈 횟수를 log2(exp)번으로 줄인다.
 * 예) 3^13, 13 = 1101(2) → 3^13 = 3^8 × 3^4 × 3^1
 * 반복 k번째에 base는 (원래 밑)^(2^k)이고, exp의 k번째 비트가 1이면 result *(원래 밑)^(2^k)
 */
int ipow(int base, int exp) {
    int result = 1;

    // exp 의 2진수 자릿수만큼 반복
    while (exp > 0) {
        if (exp & 1) { // LSB가 1
            result *= base;
        }

        base *= base; // 다음에 곱할 base
        exp >>= 1;

        // int * int -> overflow check
        if (exp > 0) {
            long long next = (long long)base * base;
            if (next > INT_MAX || next < INT_MIN) { /* int 범위 체크 */
                fprintf(stderr, "오버플로우");
                exit(1);
            }
            base = (int)next;
        }
    }
    return result;
}
