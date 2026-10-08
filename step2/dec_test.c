#include <stdio.h>

int add(int a, int b);   // 선언(프로토타입)


int main(void) {
    int result = add(3, 4);   // 이제 OK. 
    printf("%d\n", result);
    return 0;
}

int add(int a, int b) {       // 정의: 실제 몸통. 선언과 모양이 일치
    return a + b;
}