/*
[문제43] 문자열 내에 포함된 숫자의 총합 구하기
적당한 길이의 문자열을 입력받아 그 안에 존재하는 숫자들의 총 합을 계산하여 출력한다.
단, 입력된 문자열 내에 포함된 숫자는 모두 양수이다.
1) 실행 예
숫자가 포함된 문자열을 입력해주세요: ab15f#43
숫자들의 합: 13
*/

// 문자열 -> 문자를 담고 있는 배열

#include <ctype.h> // isdigit()
#include <stdio.h>
#define BUF_SIZE 100

int sum_digits(const char *s);

int main(void) {

    char buf[BUF_SIZE];
    // char new[BUF_SIZE]; // 새로운 물자열을 만들어줄 땐 꼭 마지막에 '\0' 넣어주기!!

    printf("숫자가 포함된 문자열을 입력해주세요: ");
    fflush(stdout);
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        return 1;
    }

    int result = sum_digits(buf);

    printf("%d\n", result);
    return 0;
}

int sum_digits(const char *s) {
    int sum = 0;
    for (size_t i = 0; s[i] != '\0'; i++) {
        int c = (unsigned char)s[i];
        if (isdigit(c)) {
            sum += c - '0';
        }
    }

    return sum;
}
