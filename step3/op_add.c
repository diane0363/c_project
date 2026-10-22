#include <stdint.h> // uint8_t
#include <stdio.h>

// Vx = (Vx + Vy)의 하위 8비트
// 합이 255를 넘으면 *vf = 1, 아니면 *vf = 0
void op_add(uint8_t *vx, uint8_t vy, uint8_t *vf);

static void test(uint8_t x0, uint8_t y0) {
    uint8_t V[16] = {0};              // V0~VF 전부 0
    V[0x1] = x0;                      // opcode 0x8124 흉내: x=1
    V[0x2] = y0;                      //                    y=2
    op_add(&V[0x1], V[0x2], &V[0xF]); // V1 += V2, 캐리 → VF
    printf("%3u + %3u -> V1=%3u, VF=%u\n", x0, y0, V[0x1], V[0xF]);
}

int main(void) {
    test(200, 100);
    test(100, 50);
    test(255, 1);
    test(0, 0);
    return 0;
}

// 아니 근데 vx는 주소를 넘기면서 왜 vy는 변수를 넘겨?????????
// 아 어차피 더했을 때 255뺀 값만 vx에 저장해서 남길거니까???/ 오케이 이해 완.
// 하.
void op_add(uint8_t *vx, uint8_t vy, uint8_t *vf) {
    uint8_t p = 0;
    // uint 는 overwrap이 된다.
    p = *vx + vy; //
    if (p < *vx) {
        *vf = 1;
    }
    *vx = p;
}

/*
에일리어싱 케이스 op_add(&V[0xF], V[0x1], &V[0xF]);,
즉 8Fy4에서 vx와 vf가 같은 주소를 가리킵니다.
여러분의 구현에서 최종 V[0xF]는 합의 하위 8비트가 됩니까, 플래그가 됩니까?
테스트를 직접 추가해서 확인하십시오. (명세상 정답은 플래그입니다.)
*/
