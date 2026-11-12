/*
[문제46] 문자열의 자릿수에 맞춰 길이 출력하기
두 개의 문자열을 입력 받아 입력한 각각의 문자열의 뒷부분에 길이를 출력하는 코드를 작성하시오
1) 실행결과
* 성씨를 입력하시오 : Jennifer
* 이름을 입력하시오 : Lopez
Jennifer Lopez
       8     5

*/

#include <stdio.h>

int read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    char *first_name[100];
    char *last_name[100];

    // 성 입력 받기
    printf("* 성씨를 입력하시오 : ");
    fflush(stdout);
    if (fgets(last_name, sizeof last_name, stdin) == NULL) {
        fprintf(stderr, "잘못 입력");
        return 1;
    }

    // 마지막에 꼭 '\0' 붙이기!!!
    last_name[strcspn(last_name, "\n")] = '\0';

    // 이름 입력 받기
    printf("* 이름을 입력하시오 : ");
    fflush(stdout);
    if (fgets(first_name, sizeof first_name, stdin) == NULL) {
        fprintf(stderr, "잘못 입력");
        return 1;
    }

    first_name[strcspn(first_name, "\n")] = '\0';

    return 0;
}

int read_line(const char *prompt, char *buf, size_t size) {
}
