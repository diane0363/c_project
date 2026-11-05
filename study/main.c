/*
[문제45] 문자열 제어함수 작성
System Library 중 문자열과 관련된 중요 함수인 strcpy(), strlen(), strcmp(), strcat() 함수가 있다.
이 함수와 동일한 동작을 하는 ustrcpy(), ustrlen(), ustrcmp() 라는 이름의 사용자 정의 함수를 작성하고 테스트 하는 코드를 작성하시오
1) 함수 Prototype
// 1. 문자열의 길이 반환
unsigned int ustrlen(const char *str) // 4바이트 반환
size_t ustrlen(const char *str) // 8바이트 반환
// 2. 두 문자열 s1과 s2를 사전순으로 비교
// 두 문자열 같으면 0, s1이 작으면 음수, 크면 양수)
int ustrcmp(const char *s1, const char *s2)
// 3. src 문자열을 dest 문자열 끝에 연결 (Pointer 사용)
char *ustrcat(char *dest, const char *src)
// 4. src 문자열을 dest 문자열에 덮어씌움
char *ustrcpy(char *dest, const char *src)
*/

#include <stdio.h>

size_t ustrlen(const char *str);

int ustrcmp(const char *s1, const char *s2);

char *ustrcat(char *dest, const char *src);

char *ustrcpy(char *dest, const char *src);

int main(void) {

    return 0;
}

/*
입력된 문자열의 길이 계산
*/
size_t ustrlen(const char *str) {
    char *p = &str;

    while (*p != '\0') {
        p++;
    }

    return p - str;
}

// size_t ustrlen(const char *str) {
//     char *p = &str;
//     size_t len = 0;

//     while (*p != '\0') {
//         len++;
//         *p++;
//     }

//     return len;
// }

/*
두 문자열 s1과 s2를 사전순으로 비교
- 두 문자열 같으면 0, s1이 작으면 음수, 크면 양수
*/
int ustrcmp(const char *s1, const char *s2) {
    char *p1 = &s1;
    char *p2 = &s2;

    while (true) {
        if (*p1 == '\0' || *p2 == '\0') {
            if (*p1 == '\0' && *p2 == '\0')
                return 0;
            else if (*p1 == '\0')
                return -1;
            else if (*p2 == '\0')
                return 1;
        } else if (*p1 == *p2) {
            p1++;
            p2++;
            continue;
        } else if (*p1 > *p2) {
            return 1;
        } else if (*p1 < *p2) {
            return -1;
        }
    }
}

/*
3. src 문자열을 dest 문자열 끝에 연결 (Pointer 사용)
*/
char *ustrcat(char *dest, const char *src) {
    int len = ustrlen(dest);
    char *pd = &dest;
    char *ps = &src;

    pd = pd + len;
    while (*ps != '\0') {
        *pd++ = *ps++;
    }
}

char *ustrcpy(char *dest, const char *src);
