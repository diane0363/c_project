/*
[문제25] 입력한 정수까지 존재하는 모든 소수 구하기 (함수 사용하지 않음)
정수를 입력 받아 해당 정수까지 존재하는 모든 소수를 출력하고 소수의 개수가 몇 개인지 출력하는 코드를 작성하시오
1) 조건
이중 for문 사용할 것
숫자 2도 소수이므로 2를 입력했을 때에도 처리해야 한다.
2) 실행 결과
정수 입력: 2
2
2~2까지 소수의 개수는 1개입니다

정수 입력: 11
2 3 5 7 11
2~11까지 소수의 개수는 5개입니다
*/

#include <stdbool.h>
#include <stdio.h>

int main(void) {
    int num;

    printf("정수 입력: ");
    fflush(stdout);
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "정수만 입력 가능");
        return 1;
    }

    int pr_cnt = 0;
    for (int i = 2; i <= num; i++) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            pr_cnt++;
        }
    }

    printf("2~%d까지 소수의 개수는 %d개입니다\n", num, pr_cnt);

    return 0;
}

/*
방법 1
    for (int i = 2; i <= num; i++) {
        // i가 소수인지 체크
        for (int j = 2; j <= i; j++) {
            if (i % j == 0 && i != j) {
                break; // i가 소수가 아니면 break
            }
            // 본인과 나눌 때까지도 break 되지 않았다면 소수 카운트
            if (i == j) {
                pr_cnt += 1;
            }
        }
    }
*/

/*
방법2 & 디버깅 결과
    for (int i = 2; i <= num; i++) {
        is_prime = true;
        // i 가 아니라 num을 기준으로 j값이 돈다.
        // 2,3 걸리지 않음
        for (int j = 2; j * j <= num; j++) { // line 35
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime == true) {
            pr_cnt++;
        }
    }

** 문제 1 **
(gdb) i lo
j = 2
i = 2
num = 11
is_prime = true
pr_cnt = 0

** 문제 2 **
(gdb) b 35
Breakpoint 1 at 0x1415: file main.c, line 35.
(gdb) r
Starting program: /home/di/c_project/study/main
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
정수 입력: 2
2~2까지 소수의 개수는 1개입니다
[Detaching after fork from child process 28832]
==28818==LeakSanitizer has encountered a fatal error.
==28818==HINT: For debugging, try setting environment variable LSAN_OPTIONS=verbosity=1:log_threads=1
==28818==HINT: LeakSanitizer does not work under ptrace (strace, gdb, etc)
[Inferior 1 (process 28818) exited with code 01]
-----------------------------------------------------------------------------
(gdb) b 35
Note: breakpoint 1 also set at pc 0x555555555415.
Breakpoint 2 at 0x555555555415: file main.c, line 35.
(gdb) r
Starting program: /home/di/c_project/study/main
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
정수 입력: 3
2~3까지 소수의 개수는 2개입니다
[Detaching after fork from child process 29637]
==29625==LeakSanitizer has encountered a fatal error.
==29625==HINT: For debugging, try setting environment variable LSAN_OPTIONS=verbosity=1:log_threads=1
==29625==HINT: LeakSanitizer does not work under ptrace (strace, gdb, etc)
[Inferior 1 (process 29625) exited with code 01]
*/
