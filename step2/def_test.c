#include <stdio.h>

int main(void) {
    int result = add(3, 4);   // 컴파일러가 add 함수를 찾지 못 함 # warning: implicit declaration of function 'add'
    printf("%d\n", result);
    return 0;
}

int add(int a, int b) {        // add는 여기 있지만, main보다 아래라 main에서 찾지 못함 
    return a + b;
}