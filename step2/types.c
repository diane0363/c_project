// wraparound: uint8_t에 255를 넘기면 예외도, 자동 확장도 없다. 
// 256은 0으로, 257은 1로 조용히 돌아간다. (256을 256으로 나눈 나머지)

#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint8_t reg = 250;
    reg = reg + 10;              // 260 → 범위 초과 → 260 % 256 = 4
    printf("reg = %u\n", reg);   // 출력: reg = 4  (260 아님!) & python의 경우 260, java는 음수 변환
    return 0;
}