/*
[문제42] 2차원 배열 NxN를 선언하고 𝒓𝒐𝒘^𝒄𝒐𝒍 값을 구하는 프로그램을 작성하시오
- 실행 결과 참고
1) 실행결과
  1     2     3     4     5
  2     4     8    16    32
  3     9    27    81   243
  4    16    64   256  1024
  5    25   125   625  3125
*/

#include <stdio.h>

#define N 5

void arr_print(int (*arr)[N], int rows);

int main(void) {

    int arr[N][N]; // 타입은 int[N][N]. 함수에 넘기면 int (*)[N]

    // row 순환
    for (int r = 0; r < N; r++) {
        // col 순환
        for (int c = 0; c < N; c++) {

            if (r == 0) {
                arr[r][c] = c + 1;
            } else if (c == 0) {
                arr[r][c] = r + 1;
            } else {
                arr[r][c] = (r + 1) * arr[r][c - 1];
            }
        }
    }

    // 배열 출력
    arr_print(arr, N);

    return 0;
}

void arr_print(int (*arr)[N], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < N; j++) {
            printf("%5d", arr[i][j]);
        }
        printf("\n");
    }
}
