/*
[문제32] 요일 구하기
년/월을 입력한 후 해당 월의 1일이 무슨 요일인지 구하는 프로그램을 작성하시오,
(참고 : 서기 1년 1월 1일은 월요일)
1) 실행 예
연도와 월을 차례로 입력: 2026 1
2026년1월1일 목요일
*/
#include <stdbool.h>
#include <stdio.h>

bool is_leap_year(int year);

int main(void) {
    int year = 0;
    int month = 0;
    int days = 0;
    static const int days_of_month[] = {31, 28, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};
    // int days_of_leap_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static const char *const weekdays[] = {
        "월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일",
    };

    printf("연도와 월을 차례로 입력: ");
    fflush(stdout);
    if (scanf("%d", &year) != 1 || year < 1 || year > 9999) {
        fprintf(stderr, "1이상의 정수 입력\n");
        return 1;
    }

    // month 입력값 검증 안 하면 배열 범위 밖 접근
    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
        fprintf(stderr, "1이상의 정수 입력\n");
        return 1;
    }

    // 입력 받은 연도 직전까지 일수 구하기
    for (int i = 1; i < year; i++) {
        if (is_leap_year(i)) {
            days += 366;
        } else {
            days += 365;
        }
    }

    // 전월까지의 일수 구하기
    // 1월이면 계산X, 2월이면 1월 포함(인덱스 0)
    for (int i = 0; i < month - 1; i++) {
        days += days_of_month[i];
    }

    if (month > 2 && is_leap_year(year)) {
        days += 1;
    }

    // 요일 찾기
    printf("%d년%d월1일 %s\n", year, month, weekdays[days % 7]);
    return 0;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
