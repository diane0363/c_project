#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // (1) char는 정수
    // char ch = 'C';                 // 67
    char ch = '0';                    // 48
    printf("(1) %d\n", ch);       

    // (2) 문자→숫자 변환 트릭
    char digit = '7';
    int num = digit - '0';
    printf("(2) %d\n", num);          // 문자 '7'을 숫자 7로?

    // (3) 조건식: 0이 아니면 참
    if (-1) printf("(3) yes\n"); else printf("(3) no\n");

    // (4) bool
    bool flag = (10 > 3);
    printf("(4) %d\n", flag);         // true는 1

    // (5) 함정 : 조건식에서 대입 가능 
    int x = 10;
    if (x = 0) printf("(5) run\n"); else printf("(5) skip\n");
    printf("(5) x = %d\n", x);        // 0
    return 0;
}