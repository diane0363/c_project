/*
[문제41] 2차원 정수 배열의 합 구하여 출력
5행 5열짜리 2차원 int 배열의 열의 합을 구하시오.
배열의 각 방의 데이터를 임의로 저장한 후 대각선의 합, 대각선 상단의 합, 대각선 하단의 합을 구하여 출력하는 프로그램을 작성하시오.
2) 실행 예
0번 행:   4  10   6   5  10
1번 행:   9   1   9   6   3
2번 행:   7   8   4   6   9
3번 행:   5   5   2   6   3
4번 행:   8   4   4  10   5
sum1 = 20
sum2 = 67
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int arr[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = (rand() % 100) + 1;
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    // 대각선 상단의 합
    int sum1 = 0;
    for (int i = 0; i < 5; i++) {
        sum1 += arr[i][i];
    }

    // 대각선 하단의 합
    int sum2 = 0;
    for (int i = 0; i < 5; i++) {
        sum2 += arr[i][4 - i];
    }

    printf("sum1 : %d\t", sum1);
    printf("sum2 : %d\n", sum2);

    return 0;
}
