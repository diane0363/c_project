/*
[문제44] 입력된 문자열이 회문인지 여부 확인하기
회문(Palindrome)이란 앞으로 읽으나 뒤로 읽으나 차이가 없는 단어들을 말한다.
예를 들어서“level”, “bob”과 같은 단어들은 회문에 속한다.
인자로 전달되는 문자열이 화문인지 아닌지를 검사하여 주는 사용자 정의 함수를 구현하여 처리하며. 이 함수는 회문인 경우는1을 리턴하고
아닐 경우는0을 리턴.
이때 입력된 단어가 대, 소문자 섞여 입력되더라도 구분할 수 있어야 한다. (“Level”로 입력되더라도 회문으로 인식되어야 함.)
1) 실행 예
문자열 입력: Korea
‘Korea’는 회문이 아닙니다.
문자열 입력: Level
‘Level’는 회문입니다.
2) 함수 Prototype
int palindrome(char *cp);
int myToLower(int ch);
int myToUpper(int ch);
*/

#include <stdio.h>
#include <string.h> // strlen(), strcspn()
#define BUF_SIZE 100

int palindrome(const char *cp); // 문자열을 읽기만 하므로 const 추가
int myToLower(int ch);
int myToUpper(int ch);

int main(void) {
    char buf[BUF_SIZE];

    // 문자열 입력 받기
    printf("문자열 입력: ");
    fflush(stdout);
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        fprintf(stderr, "몰라..");
        return 1;
    }

    int result = palindrome(buf);

    char buf2[BUF_SIZE];
    memcpy(buf2, buf, strcspn(buf, "\n")); // 이렇게 되면 '\0' 공간 X

    if (result) {
        printf("'%s'는 회문입니다.\n", buf2);
    } else {
        printf("'%s'는 회문이 아닙니다.\n", buf2);
    }

    return 0;
}

/*
전달된 문자열의 회문 여부 검사
회문이면 1, 아니면 0 리턴
*/
int palindrome(const char *cp) {
    int left = 0, right = strcspn(cp, "\n") - 1;
    while (right - left > 1) {
        if (myToLower(cp[left++]) == myToLower(cp[right--])) {
            continue;
        } else {
            return 0;
        }
    }

    // 검사 완료 -> 회문 성공
    return 1;
}

int myToLower(int ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    } else {
        return ch;
    }
}

int myToUpper(int ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A');
    } else {
        return ch;
    }
}
