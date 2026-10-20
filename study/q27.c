/*
[문제27] 약수 구하기
키보드로부터 정수 n을 입력 받아 n까지의 모든 약수 출력하는 프로그램을 구하시오
1) 실행 결과
정수 입력 : 14
1
2
7
14
*/

#include <stdio.h>
int main(void) {
    // 초기화를 안 하면 쓰레기값이 들어간다.
    int n = 0;
    printf("정수 입력 : ");
    fflush(stdout);
    if (scanf("%d", &n) != 0 || n < 1) {
        fprintf(stderr, "1以上の整数のみ入力");
        return 1;
    };

    int div;
    for (div = 1; div * div <= n; div++) {
        if (n % div == 0) {
            printf("%d\n", div);
        }
    }

    for (div = div - 1; div >= 1; div--) {
        if (n % div == 0 && div * div != n) {
            printf("%d/n", n / div);
        }
    }

    return 0;
}

/*
    //
    for (int div = 1; div <= n; div++) {
        if (n % div == 0) {
            printf("%d\n", div);
        }
    }
*/
