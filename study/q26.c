/*
[문제26] 모든 알파벳 출력하기
반복문을 이용하여 대문자 'A'에서 소문자 'z'까지의 ASCII값을 아래와 같이 출력하시오
이때 알파벳 사이 특수문자는 출력하지 말 것.
한 줄당 5개씩 출력하고, 소문자가 시작되면 새로운 줄로 바꿀 것. for, continue, break 중 사용
1) 실행결과
A = 65  B = 66  C = 67  D = 68  E = 69
F = 70  G = 71  H = 72  I = 73  J = 74
*/

#include <stdio.h>

int main(void) {
    int start = 'A';
    int end = 'z';

    // A ~ z 까지 출력
    int l_cnt = 0;
    for (start; start <= end; start++) {
        if (start > 'Z' && start < 'a') {
            continue;
        }
        printf("%c = %d\t", start, start);
        if (++l_cnt % 5 == 0) {
            printf("\n");
        }
        if (start == 'Z' || start == 'z') {
            printf("\n");
            l_cnt = 0;
        }
    }
    return 0;
}
