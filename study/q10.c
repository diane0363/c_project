/*
[문제10] 세 수의 정렬
세 가지 수를 입력 받아 세 가지 수 중에 가장 큰 수부터 내림차순으로 정렬 하시오. 
1) 실행 결과
1번째 수 입력 : 56
2번째 수 입력 : 45
3번째 수 입력 : 89
89   56   45

*/

#include <stdio.h>

void swap(int*, int*);

int main(void)
{
  int n1, n2, n3;

  printf("1번째 수 입력 : ");
  fflush(stdout);
    if (scanf("%d", &n1) != 1) {
        fprintf(stderr, "정수를 입력해야 합니다.\n");
        return 1;
    }

  printf("2번째 수 입력 : ");
  fflush(stdout);
    if (scanf("%d", &n2) != 1) {
        fprintf(stderr, "정수를 입력해야 합니다.\n");
        return 1;
    }

  printf("3번째 수 입력 : ");
  fflush(stdout);
    if (scanf("%d", &n3) != 1) {
        fprintf(stderr, "정수를 입력해야 합니다.\n");
        return 1;
    }

  /* 변수의 주소를 넘겨야 함수가 원본 변경 가능 (step4의 suar참고)*/
  swap(&n1, &n2);
  swap(&n1, &n3);
  swap(&n2, &n3);

  printf("%d\t%d\t%d\n", n1, n2, n3);

  return 0;
}


void swap(int *a, int *b)
{
  int tmp = 0; 

  if(*a >= *b) {
    return; // 순서가 맞으면 함수 종료
  } 

  tmp = *a;
  *a = *b;
  *b = tmp;

}


