/*
[문제28] 반복문을 이용해 구구단 출력
아래와 같이 구구단 2~9단까지 전체를 출력하는 코드를 작성하시오.
1) 실행결과
2 x 1 = 2
2 x 2 = 4
...
3 x 1 = 3
...
9단까지 출력
*/

#include <stdio.h>

int main(void) {
    for (int dan = 2; dan <= 9; dan++) {
        for (int i = 1; i <= 9; i++) {
            printf("%d x %d = %d\n", dan, i, dan * i);
        }
    }
    return 0;
}

/*
    for (int n2 = 1; n2 <= 9; n2++) {
        printf("%d x %d = %d\n", n1, n2, n1 * n2);
        if (n2 == 9 && n1 < 9) {
            n2 = 0;
            n1++;
        }
    }
*/
