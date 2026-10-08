// checksec --file=./canary_test 시 함수 안에 보호할 버퍼가 생기면 카나리 on

/* strcpy
char *strcpy(char *dest, const char *src);
char *my_strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++) != '\0')
        ;
    return ret;
}

하지만 strcpy는 buf의 크기를 모른다. 그냥 /0을 만날 때까지 복사. 
=> 오버플로 발생 가능성 O
*/

#include <stdio.h>
#include <string.h>
void foo(char *s) {
    char buf[16];       // ← 스택 버퍼 등장 → 카나리 트리거
    strcpy(buf, s);
    printf("%s\n", buf);
}

// main : 런타임 실행 함수 
// argc 단어개수, argv 명령어 담은 배열 
// -> 런타임이 명령어 수를 세서 argc에 수를 넣고 각각 argv 배열에 담아 전달
// gdb 파일명 -> run AAAA -> 런타임 시 들어가는 명령문은 '파일명 AAAA' 
// argc는 2, argv는 [파일명, AAAA, Null]
int main(int argc, char **argv) {
    if (argc > 1) foo(argv[1]); // argc가 인자가 있으면, foo함수에 첫번째 인자를 넣어랑
    return 0;
}