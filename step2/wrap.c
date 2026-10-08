#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t  a = 200;
    uint8_t  b = 100;
    uint8_t  sum = a + b;            // (1) 200+100 = ?
    printf("(1) sum  = %u\n", sum);

    uint8_t  x = 0;
    x = x - 1;                        // (2) 0에서 1 빼면?
    printf("(2) x    = %u\n", x);

    uint16_t big = 300;               // (3) 300은 uint16_t엔 들어가나?
    printf("(3) big  = %u\n", big);

    uint8_t  cut = (uint8_t)big;      // (4) 300을 8비트로 자르면?
    printf("(4) cut  = %u\n", cut);

    uint16_t opcode = 0xABCD;         // (5) CHIP-8 opcode 예시
    uint8_t  high   = opcode >> 8;    // 상위 8비트만
    printf("(5) high = 0x%02X\n", high);
    return 0;
}