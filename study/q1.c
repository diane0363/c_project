/*
[문제1] 적정 체중 구하기출력문과 -, * 연산자만을 이용하여 적정 체중을 구하여 출력하는 프로그램을 작성하시오 

1) 공식 (키(cm) - 100) * 0.9 = 적정체중
2) 실행 결과 만약 키가 180cm라면 아래와 같이 출력된다. (소수점 이하 1자리 출력)
키 180.0cm의 적정 체중은 72.0kg이다.
*/

#include <stdio.h> // printf

int main(void)
{
  float height = 180;
  float weight = (height - 100) * 0.9;
  
  // printf("값: %.1f", weight);
  printf("값: %.1f\n", weight);

  return 0; // OS에 "정상 종료"를 알림

}