/*
[문제26] 모든 알파벳 출력하기
반복문을 이용하여 대문자 'A'에서 소문자 'z'까지의 ASCII값을 아래와 같이 출력하시오
이때 알파벳 사이 특수문자는 출력하지 말 것.
한 줄당 5개씩 출력하고, 소문자가 시작되면 새로운 줄로 바꿀 것. for, continue, break 중 사용
1) 실행결과
A = 65  B = 66  C = 67  D = 68  E = 69
F = 70  G = 71  H = 72  I = 73  J = 74
*/
/*
비트 연산 : ^ (비트 스위치?)
알파벳 : 32 차이 (A:65, a:97), A~Z 26 (Z:90)
    => 0010 0000 (2^5)
*/
#include <stdio.h>

int main(void) {
    int alp = 'A';
    int end = 'Z';

    // A ~ Z 까지 출력
    // for (alp; alp < (alp + 26); alp++) { // 영원히 멈추지 않아...
    for (alp; alp <= end; alp++) {
        int l_cnt = 0;
        printf("%c = %d\t", alp, alp);
        if (l_cnt++ && l_cnt == 5) {
            printf("\n");
        }
    }
    // a ~ z 까지 출력 alp ^ 0x20
    end = end ^ 0x20;
    alp = (end - 26) ^ 0x20;
    for (alp; alp <= end; alp++) {
        int l_cnt = 0;
        printf("%c = %d\t", alp, alp);
        if (l_cnt++ && l_cnt == 5) {
            printf("\n");
        }
    }

    return 0;
}
/*
        if (alp == end && alp != 'z') {
            alp = alp ^ 0x20;
            end = end ^ 0x20;
            printf("\n");
        }
*/
