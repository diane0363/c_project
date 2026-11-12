/*
[문제46] 문자열의 자릿수에 맞춰 길이 출력하기
두 개의 문자열을 입력 받아 입력한 각각의 문자열의 뒷부분에 길이를 출력하는 코드를 작성하시오
1) 실행결과
* 성씨를 입력하시오 : Jennifer
* 이름을 입력하시오 : Lopez
Jennifer Lopez
       8     5

*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

// 문자열을 입력받아 배열에 담기
bool read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    // 이렇게 사용하면 VLA. 크기가 고정된 배열은 define 사용
    // int size = 100;
    char first_name[BUF_SIZE];
    char last_name[BUF_SIZE];

    // 성 입력 받기
    if (read_line("* 성씨를 입력하시오 : ", last_name, sizeof last_name)) {
        return 0;
    }
    // 이름 입력 받기
    if (read_line("* 이름을 입력하시오 : ", first_name, sizeof first_name)) {
        return 0;
    }

    // 배열 수 세기
    int l_len = strlen(last_name);
    int f_len = strlen(first_name);

    // 값 출력 - *은 출력폭을 인자로 받음
    printf("%s %s\n", first_name, last_name);
    printf("%*d %*d\n", f_len, f_len, l_len, l_len);

    return 0;
}

/*
사용자의 입력을 받고 배열에 담는 함수
성공하면 true, EOF 등 실패하면 false
prompt : 화면에 보여줄 질문
buf : 입력 담을 배열
size : 배열의 바이트
*/
bool read_line(const char *prompt, char *buf, size_t size) {

    // printf(prompt);  => 이렇게 쓰면 prompt를 문자 서식으로 인식한다!!!
    // 1.
    // printf("%s", prompt);
    // fflush(stdout);
    // 2.
    fputs(prompt, stdout);

    // sizeof buf가 아닌 sizeof size를 쓰는 이유는??
    if (fgets(buf, size, stdin) == NULL) {
        fprintf(stderr, "실패");
        return 0;
    }

    buf[strcspn(buf, "\n")] = '\0';

    return 1;
}
