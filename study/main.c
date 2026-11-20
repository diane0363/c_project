/*
[문제48] 앞서 작성한 함수를 이용해서 지정한 년도 특정 달의 한달 치 달력을 구현해 보자.
①윤년 구하는 함수 (isLeapYear(int year))
②총 날수 구하는 함수 (totalDays(int year))
③특정 년도 특정 달의 1일이 무슨 요일인지 구하기
※ 달력을 출력할 때 다음 페이지에서 제공하는 gotoxy() 함수를 이용하여 출력위치를 지정할 수 있다.
-> 기존 제공(windows.h)은 window기준. 현재 환경은 LINUX이므로 사용 X -> ANSI 이스케이프 시퀀스 혹은 ncurses라는 라이브러리 사용
 ** 서기 1년 1월 1일은 월요일
*/
#include <stdbool.h>
#include <stdio.h>

bool is_leap_year(int year);
int total_days(int year);

int main(void) {
    int year, month;
    // 가독성을 위해 분리
    int total_day = 0;
    int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 년도와 달 입력받기
    printf("연도를 입력하시오 : ");
    fflush(stdout);
    if (scanf("%d", &year) != 1 || year > 9999) {
        fprintf(stderr, "1~9999년만 입력\n");
        return 1;
    }

    printf("월을 입력하시오 : ");
    fflush(stdout);
    if (scanf("%d", &month) != 1 || month > 12 || month < 1) {
        fprintf(stderr, "1~12월만 입력\n");
        return 1;
    }

    // 해당 1일의 요일 구하기
    // 전년도까지의 일 수 총합
    // 0년 부터 계산 -> 1부터 시작으로 변경
    for (int i = 1; i < year; i++) {
        total_day += total_days(i);
    }

    // 해당 년, 해당 월까지의 일수 총합
    // 년도 실수와 동일: 시작을 0 -> 1
    for (int j = 1; j < month; j++) {
        total_day += daysOfMonth[j - 1];
        if (is_leap_year(year) && j == 2) {
            total_day += 1;
        }
    }

    // 1 : 월요일 -> 1년 1월 -> total_day : 0
    int first_weekday = total_day % 7;

    // 달력 출력
    printf("mon\ttue\twed\tthu\tfri\tsat\tsun\n");

    for (int t = 0; t < first_weekday; t++) {
        putchar('\t');
    }

    int current_day = daysOfMonth[month - 1];
    if (is_leap_year(year) && month == 2) {
        current_day += 1;
    }

    for (int d = 1; d < current_day + 1; d++) {
        printf("%d\t", d);
        if ((first_weekday + 1) % 7 == 0) {
            printf("\n");
        }
        first_weekday++;
    }

    printf("\n");
    return 0;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int total_days(int year) {
    if (is_leap_year(year)) {
        return 366;
    } else {
        return 365;
    }
}
