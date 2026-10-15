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

int swap(int*, int*);

int main(void)
{
  // 포인터는 이미 존재하는 것을 가리킬 때만 쓸모가 있다. 가리킬 대상이 없다면, 대상을 먼저 만들어야한다. 
  int *n1, *n2, *n3;

  printf("1번째 수 입력 : ");
  fflush(stdout);
  scanf("%d", n1);

  printf("2번째 수 입력 : ");
  fflush(stdout);
  scanf("%d", n2);

  printf("3번째 수 입력 : ");
  fflush(stdout);
  scanf("%d", n3);

  swap(n1, n2);
  swap(n1, n3);
  swap(n2, n3);

  printf("%d\t%d\t%d\n", *n1, *n2, *n3);

  return 0;
}

int swap(int *max, int *min)
{
  int *tmp = 0; // 무조건 초기화를 해줘야하나? -> 포인터를 선언할 대 가리킬 대상이 아직 없다면 NULL로 초기화하는 것이 좋은 습관. 
  // 역참조 시 쓰레기 주소에 접근해 크래시 혹은 다른 변수 덮어쓸 가능성 있음
  // if (tmp == NULL) 검사 가능 -> 버그를 없애주지는 않아도, 버그 체크 용이 증가.
  // 그리고, tmp는 값 보관 용이니 포인터일 필요 X
  
  // 해당 주소에 값을 바꾸는 것, 주소값을 바꾸는 것 어떤 것이 좋을까?
  // 주소값을 바꿔도 함수 안에서 사용한 지역 변수는 사라진다. 
  if(*max < *min) {
    *tmp = *max;
    *max = *min;
    *min = *tmp;
  }

  return 0;

}