/*
[문제38] 입력 받은 값으로 배열 채우기
길이가 10인 정수 배열을 선언하고 총 10개의 정수를 입력 받아 숫자가 홀수이면 배열의 앞에서부터 채워나가고, 짝수이면 뒤에서부터 채워
나가는 코드를 작성하시오
1) 실행 예
사용자가 입력한 값 전체
1 2 3 4 5 6 7 8 9 10
완료된 배열
1 3 5 7 9 10 8 6 4 2
*/

#include <stdio.h>

int main(void) {
    int arr[10];
    int num, right = 0, left = 9;

    printf("정수 10개를 입력하시오 : ");
    fflush(stdout);

    // 입력 값 받기
    while (right <= left) {

        if (scanf("%d", &num) != 1 || num < 1) {
            fprintf(stderr, "1이상의 정수를 입력하시오\n");
            while (getchar() != '\n') {
            }
            continue;
            // return 1;
        }

        if (num % 2 == 1) {
            arr[right++] = num;
        } else {
            arr[left--] = num;
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    return 0;
}
