/*
[문제5] 산술 연산자의 사용한 거스름돈 출력
상품의 가격, 받은 돈을 입력 받아 거스름돈을 출력하는 프로그램을 작성하시오.
상품금액은 받은 돈보다 작은 값으로 입력되어야 한다.
1) 실행 결과
상품 금액을 입력하세요 : 5400
받은 돈을 입력하세요 : 6000
거스름돈은 600원입니다.


*/

#include <stdio.h>

int main(void) {
    int price;
    int payment;
    int change;

    printf("상품 금액을 입력하세요 : ");
    fflush(stdout); // 사용자 입력 대기
    if (scanf("%d", &price) != 1) {
        fprintf(stderr, "상품 금액은 양의 정수로 입력\n");
        return 1;
    };

    printf("받은 돈을 입력하세요 : ");
    fflush(stdout);
    if (scanf("%d", &payment) != 1) {
        fprintf(stderr, "받은 돈은 양의 정수로 입력\n");
        return 1;
    }

    if (payment < price) {
        fprintf(stderr, "받은 돈은 상품 금액보다 크거나 같아야\n");
        return 1;
    }

    change = payment - price;
    printf("거스름 돈은 %d원입니다.\n", change);
    return 0;
}
