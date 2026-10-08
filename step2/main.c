// ===== main.c (사용) ===== cpu.h & cpu.c 참고
/*
#include <stdio.h> → 시스템/표준 라이브러리 헤더 (컴파일러 설치 경로에서 찾음)
#include "cpu.h" → 내가 만든 헤더 (현재 폴더에서 먼저 찾음)

* 컴파일 시 무조건 함께 빌드
gcc -Wall -Wextra -g -o emulator main.c cpu.c
*/
#include <stdio.h>
#include "cpu.h"       // cpu의 함수들을 "선언"으로 알게 됨

int main(void) {
    uint8_t r = cpu_add(200, 100);   // 44 (wraparound)
    printf("%u\n", r);
    return 0;
}