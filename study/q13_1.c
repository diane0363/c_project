/*
[문제13] 일수를 입력 받아 그 값을 주와 일수로 변환하는 프로그램 작성.
1) 실행 예
날수를 입력하시오 : 25
25일은 3주 4일입니다

*/

#include <stdio.h>

int main(void) {
    int day, week = 0;

    printf("날수를 입력하시오 : ");
    fflush(stdout);
    if (scanf("%d", &day) != 1) {
        fprintf(stderr, "숫자를 입력하시오.\n");
        return 1;
    }

    while (day >= 7) {
        day = day % 7;
        week = week + 1;
    }

    int init_day = 7 * week + day;

    printf("%d일은 %d주 %d일입니다.\n", init_day, week, day);
    return 0;
}

/*
[디버깅 결과]

di@KISSCO-PC01:~/c_project/study$ gdb -q ./main
Reading symbols from ./main...

(gdb) b main.c:21
Breakpoint 1 at 0x1458: file main.c, line 21.

(gdb) r
Starting program: /home/di/c_project/study/main
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
날수를 입력하시오 : 22

Breakpoint 1, main () at main.c:21
21          while (day >= 7) {

(gdb) n
22              day = day % 7;

(gdb) info locals
day = 22
week = 0
init_day = 1451542325

(gdb) n
23              week = week + 1;

(gdb) info locals
day = 1
week = 0
init_day = 1451542325

(gdb)
*/
