/*
** 반복문 버전 **
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

int main(void) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", fibonacci(i));
    }
    printf("\n");

    return 0;
}

int fibonacci(int n) {
    int prev = 1, curr = 1; /* F(1), F(2) */
    int remaining = n - 2;
    while (remaining > 0) {
        int next = prev + curr;
        prev = curr;
        curr = next;
        remaining--;
    }
    return curr;
}
