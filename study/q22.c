/*
[문제22] 띠 구하기
태어난 해를 4자리 정수로 입력 받아서 해당 년도의 띠를 출력하시오.
(switch~case사용)
- 띠 순서: 원숭이, 닭, 개, 돼지, 쥐, 소, 호랑이, 토끼, 용, 뱀, 말, 양
    - 실행 결과
        태어난 해를 입력하세요: 2021
        2021년생은 소띠입니다.

** 이 문제의 경우 문자열 배열을 쓰는 것이 더 좋다.
    - 값 → 값 매핑이면 배열, 값 → 동작이면 switch


*/

#include <stdio.h>

int main(void) {
    int year;
    // 값을 계속 바꾸는 경우, 같은 주소 값을 스는가?
    // -> 변수의 주소는 그대로, 변수에 담긴 주소는 바뀐다.
    // const char * -> 해당 '포인터'를 통해서 값을 바꾸지 않겠다.
    const char *name;

    printf("태어난 해를 입력하세요: ");
    fflush(stdout);
    if (scanf("%d", &year) != 1 || year < 1000 || year > 9999) {
        fprintf(stderr, "4자리 정수를 입력하세요.\n");
        return 1;
    }

    switch (year % 12) {
    case 0:
        //
        name = "원숭이";
        break;
    case 1:
        name = "닭";
        break;
    case 2:
        name = "개";
        break;
    case 3:
        name = "돼지";
        break;
    case 4:
        name = "쥐";
        break;
    case 5:
        name = "소";
        break;
    case 6:
        name = "호랑이";
        break;
    case 7:
        name = "토끼";
        break;
    case 8:
        name = "용";
        break;
    case 9:
        name = "뱀";
        break;
    case 10:
        name = "말";
        break;
    case 11:
        name = "양";
        break;
    default:
        // name = "?";
        name = NULL; // NULL 검사 필요
        break;
    }

    // NULL을 print로 출력하는 경우, 표준상 UB (glibc의 printf의 경우(null))
    // Java의 경우, null 출력 시 "null" & 메서드 호출 시 NullPointerException
    if (name == NULL) {
        fprintf(stderr, "내부 오류 : 띠를 결정하지 못함\n");
        return 1;
    }

    printf("%d년생은 %s띠입니다.\n", year, name);

    return 0;
}
