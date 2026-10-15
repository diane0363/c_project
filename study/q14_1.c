/*
[문제14] 지구의 공전 주기를 일 시 분 초로 변환하기

1년은 365.2422일이다. 이는 몇 일, 몇 시간, 몇 분, 몇 초 인가를 출력하시오.
(단, 마지막 초는 소수점 이하 둘째 자리까지 출력)

1) 실행 결과
365.2422일은 365일 5시간 48분 46.08초입니다
*/

#include <stdio.h>

// 1일 = 24시간 = 24*60분 = 24*60*60초
int main(void) {
    double year = 365.2422;
    int day = (int)year;

    double rest = (year - day) * 24 * 60 * 60;

    int hour = rest / (60 * 60);
    rest -= hour * 24;

    int min = rest / 60;
    rest -= min * 60;

    double sec = rest;

    return 0;
}

/*
왜 이런,,

(gdb) info locals
year = 365.24220000000003
day = 365
rest = 46.080000002184534
hour = 5
min = 346
sec = 46
(gdb)
*/
