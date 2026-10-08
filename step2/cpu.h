// ===== cpu.h (선언 모음) =====
// #ifndef CPU_H / #define CPU_H / #endif : 재선언 방지 관례!!!
#ifndef CPU_H          // ← include guard 이미 한 번 선언을 복붙한 경우 재선언(재복붙) 방지
#define CPU_H

#include <stdint.h>

void cpu_reset(void);                    // 선언
uint8_t cpu_add(uint8_t a, uint8_t b);   // 선언

#endif