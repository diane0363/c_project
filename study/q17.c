/*
[문제17] 좌표의 사분면 위치 출력하기
2차원 평면 상에 존재하는 좌표 x와 y를 정수로 입력받아 해당 좌표가 어느 분면에
존재하는지 출력하는 코드를 작성하시오 1) 실행결과 x좌표 입력 : 5 y좌표 입력 : 5
좌표 (5, 5)는 1분면에 있다.
x좌표 입력 : -5
y좌표 입력 : 5
좌표 (-5, 5)는 2분면에 있다.
x좌표 입력 : -5
y좌표 입력 : -5
좌표 (-5, -5)는 3분면에 있다.
x좌표 입력 : 5
y좌표 입력 : -5
좌표 (5, -5)는 4분면에 있다.

*/

#include <stdio.h>

int main(void) {
    int x, y, q;

    printf("x좌표 입력 : ");
    fflush(stdout);
    if (scanf("%d", &x) != 1 || x == 0) {
        fprintf(stderr, "0이 아닌 숫자를 입력하세요.\n");
        return 1;
    }

    printf("y좌표 입력 : ");
    fflush(stdout);
    if (scanf("%d", &y) != 1 || y == 0) {
        fprintf(stderr, "0이 아닌 숫자를 입력하세요.\n");
        return 1;
    }

    if (x > 0 && y > 0) {
        q = 1;
    } else if (x < 0 && y > 0) {
        q = 2;
    } else if (x < 0 && y < 0) {
        q = 3;
    } else {
        q = 4;
    }

    printf("좌표 (%d, %d)는 %d분면에 있다.\n", x, y, q);

    return 0;
}
