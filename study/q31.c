/*
[문제31] 총 일수 구하기
윤년에 해당하는 연도는 366일, 평년은 365일까지 있다.
서기 1년~입력 받은 연도까지 총 일수를 구하는 프로그램을 작성하시오.
1) 실행 예
연도 입력: 2020
서기 1년 ~ 2020년까지 총 날수: 737790
*/
#include <stdbool.h>
#include <stdio.h>

// 윤년이면 true
bool is_leap_year(int year);

int main(void) {
    int year;
    int days = 0;

    printf("연도 입력: ");
    fflush(stdout);
    if (scanf("%d", &year) != 1 || year < 1 || year > 9999) {
        fprintf(stderr, "1이상의 수를 입력하시오.\n");
        return 1;
    }

    // 입력 받은 연도까지 일수 구하기
    // 윤년이면 366, 평년이면 365
    for (int i = 1; i <= year; i++) {
        if (is_leap_year(i)) {
            days += 366;
        } else {
            days += 365;
        }
    }
    printf("%d\n", days);

    return 0;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
