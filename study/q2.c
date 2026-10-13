/*
정사각형 넓이 구하기

[문제2] 키보드의 입력을 통해 정사각형 넓이 구하기 키보드로부터 정수를 입력 받아 이 값을 한 변으로 하는 정사각형의 넓이 구하여 출력하시오

1) 공식 한 변의 길이 X 한 변의 길이 = 정사각형의 넓이

2) 실행 결과

정사각형 한 변의 길이를 입력하세요(cm) : 5 정사각형의 넓이는 25 제곱센티입니다.
*/

#include <stdio.h>

int main(void)
{
    int side;

    printf("정사각형 한 변의 길이를 입력하세요(cm) : ");
    fflush(stdout);

    if (scanf("%d", &side) != 1) {
        fprintf(stderr, "정수를 입력해야 합니다.\n");
        return 1;
    }

    /* 46340^2 = 2,147,395,600 <= INT_MAX(2,147,483,647). 곱하기 전에 막아야 UB를 피한다 */
    if (side < 0 || side > 46340) {
        fprintf(stderr, "0 이상 46340 이하의 값을 입력해야 합니다.\n");
        return 1;
    }

    printf("정사각형의 넓이는 %d 제곱센티입니다.\n", side * side);
    return 0;
}