// ====== mathutil =====================
#include <stdio.h>
#include "mathutil.h"

int main(void) {
    printf("wrap_add(200,100) = %u\n", wrap_add(200, 100));  // 예상: 300
    printf("clamp(150, 0, 100) = %d\n", clamp(150, 0, 100)); // 예상: 100
    printf("clamp(-5, 0, 100) = %d\n", clamp(-5, 0, 100));   // 예상: 0
    return 0;
}