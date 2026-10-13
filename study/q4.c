/*
[문제4] 원의 넓이 구하기
연산자만을 이용하여 반지름이 12cm인 원의 넓이 구해보기
원주율은 상수변수로 선언하고3.141592로 초기화 하시오
1) 공식
반지름 X 반지름 X 원주율(3.14) = 원의 넓이
2) 실행 결과
반지름 12cm인 원의 넓이: 452.39입니다.

*/

#include <stdio.h>

int main(void)
{
  const double PI = 3.141592;
  double r = 12;
  double circle;

  circle = r * r * PI; // 
  printf("반지름 %.0fcm인 원의 넓이: %.2f입니다.\n", r, circle);

  return 0;
}


