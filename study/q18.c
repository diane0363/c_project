/*
두 개의 좌표 중 어느 점이 원점 가까울까?
[문제18] 두 좌표 중 원점과 가까운 좌표 구하기
1사분면의 x, y 좌표 두 개를 입력 받은 후, 원점과 더 가까운 한 가지의 좌표를 출력
하시오.
1) 실행 결과
첫 번째 점의 x좌표를 입력: 1
첫 번째 점의 y좌표를 입력: 5
두 번째 점의 x좌표를 입력: 5
두 번째 점의 y좌표를 입력: 1
두점은원점과거리가같다.
첫 번째 점의 x좌표를 입력: 5
첫 번째 점의 y좌표를 입력: 5
두 번째 점의 x좌표를 입력: 2
두 번째 점의 y좌표를 입력: 2
첫번째점(5, 5)이두번째점(2, 2)보다원점에서멀리떨어져있다

*/

#include <stdbool.h>
#include <stdio.h>

bool input_num(const char *prompt, int min, int *out);

int main(void) {
    int x1, y1, x2, y2;

    // 키보드 입력
    if (!input_num("첫 번째 점의 x좌표를 입력: ", 1, &x1) ||
        !input_num("첫 번째 점의 y좌표를 입력: ", 1, &y1) ||
        !input_num("두 번째 점의 x좌표를 입력: ", 1, &x2) ||
        !input_num("두 번째 점의 y좌표를 입력: ", 1, &y2)) {
        return 1;
    }

    // 원점 - 좌표 거리 구한 후 비교
    // x^2 + y^2
    // int signed overflow 주의 -> 32767
    int r1 = x1 * x1 + y1 * y1;
    int r2 = x2 * x2 + y2 * y2;

    if (r1 > r2) {
        printf("첫 번째 점(%d, %d) 이 두 번째 점(%d, %d) 보다 원점에서 멀리 "
               "떨어져있다\n",
               x1, y1, x2, y2);
    } else if (r1 < r2) {
        printf("두 번째 점(%d, %d) 이 첫 번째 점(%d, %d) 보다 원점에서 멀리 "
               "떨어져있다\n",
               x2, y2, x1, y1);
    } else {
        printf("두 점은 원점과 거리가 같다.\n");
    }

    return 0;
}

bool input_num(const char *prompt, int min, int *out) {
    // printf(prompt);
    printf("%s", prompt);
    fflush(stdout);
    if (scanf("%d", out) != 1 || *out < min) {
        fprintf(stderr, "1이상의 정수를 입력하세요.\n");
        return false;
    }

    return true;
}
