/*
[문제15] 시간 환산
키보드로부터 정수 값에 해당하는 초 단위의 값을 입력 받아 시, 분, 초 단위로
환산하여 출력하는 프로그램을 작성하시오.
1) 실행 결과
시간을 초 단위로 입력하세요 : 2354
2354초는 0시간 39분 14초입니다.

*/

#include <stdio.h>

int main(void) {

    int time;

    printf("시간을 초 단위로 입력하세요 : ");
    fflush(stdout);
    if (scanf("%d", &time) != 1 || time < 0) {
        fprintf(stderr, "0이상의 정수를 입력하세요\n");
        return 1;
    }

    int hour = time / 3600;
    int min = (time % 3600) / 60;
    int sec = (time % 3600) % 60;

    printf("%d초는 %d시간 %d분 %d초입니다.\n", time, hour, min, sec);

    return 0;
}
