/*
[문제47] 문자열이 저장되어 있는 2차원 배열을 정렬하여 출력하는 프로그램을 완성하시오
아래 제시된 main() 함수와 함수 prototype 을 확인하여 제공된 결과와 같이 문자열이 오름차순으로 정렬되어 출력되도록 함수를 정의하시오.
메인함수 내의 2차원 배열의 문자열은 임의의 단어를 사용하여 초기화 한다.
2. 실행 결과
## 정렬 전: banana  skyblue  airplane  watermelon  father
## 정렬 후: airplane  banana  father  skyblue  watermelon
*/

#include <stdio.h>

void strSort(char (*word)[20]);              // 정렬 함수
void strOutput(char (*word)[20]);            // 문자열 출력함수
int ustrcmp(const char *s1, const char *s2); // 문자열 비교함수
char *ustrcpy(char *dest, const char *src);  // 문자열 복사함수

#define CNT 5

int main(void) {
    char word[CNT][20] = {"banana", "skyblue", "airplane", "watermelon",
                          "father"};
    printf("## 정렬 전: ");
    strOutput(word);
    strSort(word);
    printf("## 정렬 후: ");
    strOutput(word);
    return 0;
}

/*
배열의 문자열들을 오름차순으로 정렬
- 교환 법칙
*/
void strSort(char (*word)[20]) {
    char tmp[20];

    // CNT만큼 반복
    // CNT는 define으로 정의된거니까 그냥 여기서 써도 되나? 가능
    for (int i = 0; i < CNT - 1; i++) {
        for (int j = 0; j < CNT - 1; j++) {
            // 오름차순대로 비교
            if (ustrcmp(word[j], word[j + 1]) > 0) {
                // 값 변경
                // 값 변경할 때 문자열 복붙을 해야하나? 그냥 가리키는 주소만 바꾸면 안 되나? 불가능
                // 가리키는 주소같은건 없다.!!!!!!!!!!!
                ustrcpy(tmp, word[j]);
                ustrcpy(word[j], word[j + 1]);
                ustrcpy(word[j + 1], tmp);
            }
        }
    }
}

/*
문자열을 출력
*/
void strOutput(char (*word)[20]) {

    for (int i = 0; i < CNT; i++) {
        if (i > 0) {
            fputs("  ", stdout);
        }
        fputs(word[i], stdout);
    }
    // putchar : stdout에 문자 추가
    putchar('\n');
}

/*
문자열 비교 함수
*/
int ustrcmp(const char *s1, const char *s2) {

    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    return *s1 - *s2; // char 자체로 뺌
}

/*
문자열 복사 함수
*/
char *ustrcpy(char *dest, const char *src) {
    char *p = dest;

    while ((*p++ = *src++) != '\0') {
    }

    return dest;
}
