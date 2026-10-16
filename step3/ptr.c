/*
[과제 A]void swap_u8(uint8_t *a, uint8_t *b);를 구현하고, main에서 호출 전후 값을 출력하십시오.
[과제 B]CHIP-8 8xy4를 포인터로 구현하십시오.
*/

#include <stdint.h> // uint8_t
#include <stdio.h>

void swap_u8(uint8_t *a, uint8_t *b);

void op_add(uint8_t *vx, uint8_t vy, uint8_t *vf);

static void test(uint8_t x0, uint8_t y0) {
    uint8_t V[16] = {0}; // 16칸 배열을 0으로 초기화
    // V[0] 은 왜 비워? 혹시 8xy4에서 8의 자리인 것이야???
    // 8124를 그대로 구현하려고 그냥 1,2 를 쓴거라고 한다. ㅇㅋ 이해완
    V[0x1] = x0;
    V[0x2] = y0;
    // 0xF는 뭥미? V[16]이야? 아니 V[1], V[2] 는 십진순데 왜 저건 16진수임 환장하겟네. 자기 실수래 ㅋㅋ
    // 레지스터 인덱스는 항상 16진수로 씁니다. opcode의 x, y 자리와 1:1로 대응되기 때문.
    op_add(&V[0x1], V[0x2], &V[0xF]);
    // uint8_t 는 %d로 받는다고 들었는데 아니 이건 왜 %u로 받아?
    // 어차피 값의 범위가 0~255여서 %d든 %u든 같이 나온대 ㅇㅋ…
    printf("%3u + %3u -> V1=%3u, VF=%u\n", x0, y0, V[1], V[0xF]);
}

int main(void) {
    // A ---------------
    uint8_t t1 = 42;
    uint8_t t2 = 24;

    printf("t1: %d, t2: %d\n", t1, t2);
    swap_u8(&t1, &t2);
    printf("t1: %d, t2: %d\n", t1, t2);

    // B ----------------
    test(200, 100);
    test(100, 50);
    test(255, 1);
    test(0, 0);

    return 0;
}

void swap_u8(uint8_t *a, uint8_t *b) {
    // uint8_t temp;
    // temp = *a;
    uint8_t temp = *a; // 선언과 초기화 동시에
    *a = *b;
    *b = temp;
}

void op_add(uint8_t *vx, uint8_t vy, uint8_t *vf) {
}
