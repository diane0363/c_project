/*
[문제48] 앞서 작성한 함수를 이용해서 지정한 년도 특정 달의 한달 치 달력을 구현해 보자.
①윤년 구하는 함수 (isLeapYear(int year))
②총 날수 구하는 함수 (totalDays(int year))
③특정 년도 특정 달의 1일이 무슨 요일인지 구하기
※ 달력을 출력할 때 다음 페이지에서 제공하는 gotoxy() 함수를 이용하여 출력위치를 지정할 수 있다.
-> 기존 제공(windows.h)은 window기준. 현재 환경은 LINUX이므로 사용 X -> ANSI 이스케이프 시퀀스 혹은 ncurses라는 라이브러리 사용
 ** 서기 1년 1월 1일은 월요일

 * 검증 방법
    - 리눅스의 cal (cal [month] [year])
    - 1752/9 이전은 율리우스력 -> 1753이후만 비교
    - dkdk
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
    int start_day = total_day % 7;
    int current_day = daysOfMonth[month - 1];

    if (is_leap_year(year) && month == 2) {
        current_day += 1;
    }

    // 달력 출력
    printf("%10d %d\n", year, month);
    printf("mo tu we th fr sa su\n");

    for (int t = 0; t < start_day; t++) {
        // warning -> 작은 따옴표에는 글자가 하나만 + putchar은 글자 한 개만 출력
        // 문법적으로는 허용하지만 값은 컴파일러마다 다르다.
        // putchar('    ');
        fputs("   ", stdout);
    }

    for (int d = 1; d < current_day + 1; d++) {
        printf("%2d ", d);
        if ((start_day + d) % 7 == 0) {
            putchar('\n');
        }
    }
    // 일요일로 끝나지 않았을 경우
    if ((start_day + current_day) % 7 != 0) {
        putchar('\n');
    }

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
