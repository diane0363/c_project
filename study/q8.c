/*
[문제8] 자릿수 합계 구하기
키보드로 0 부터 999까지의 정수를 입력 받은 수 각각의 자릿수의 합한 결과를 출력하는 프로그램을 작성하시오.
사용자에 의한 오류 입력은 없는 것으로 간주한다.
1) 실행 결과
0~999까지의 정수입력 :456
15
0~999까지의 정수입력 :123
6
*/

#include <stdio.h>

int main(void)
{
  int num;
  // int sum; -> 기존 쓰레기값에서 더해진다.
  int sum = 0;
  
  printf("0~999까지의 정수입력 :");
  fflush(stdout);

  if (scanf("%d", &num) != 1) {
    fprintf(stderr, "0이상의 정수만 입력\n");
    return 1;
  }

  while (num > 0) {
    sum += num % 10;
    num = num / 10;
  }

  printf("%d\n", sum);
  return 0;
}

