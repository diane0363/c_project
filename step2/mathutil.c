// ===== cpu.c (정의) =====
#include "cpu.h"       // 내 선언이 정의와 일치하는지 컴파일러가 대조

void cpu_reset(void) {
    // 실제 구현
}

uint8_t cpu_add(uint8_t a, uint8_t b) {
    return a + b;      // uint8_t라 wraparound 자동
}