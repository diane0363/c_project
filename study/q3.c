/*
gcc -Wall -Wextra -Wconversion -g -fsanitize=address -o q3 q3.c && ./main
*/
/*
체질량지수 구하기
[문제3] BMI 지수 구하기 몸무게(kg)와 키(cm)를 입력 받아 BMI 지수를 구하여 출력하시오. 이때 BMI 계산의 결과는 소수 2자리까지만 출력할 것.

1) 공식 BMI = 몸무게(kg) / 키(m)의 제곱

2) 실행 결과 키(cm):165 몸무게(kg) : 67 165cm, 67Kg, BMI=24.61
*/

#include <stdio.h>

int main(void)
{
  double weight;
  double height;
  double bmi;

  printf("키(cm): ");
  fflush(stdout);
  // %f가 아닌 %lf
  // scanf 성공 후(왼쪽) 양수 평가(오른쪽)
  if (scanf("%lf", &height) != 1 || height <= 0) {     
    // 출력 대상 지정 -> fprintf(stderr,..) 앞의 f는 filestream; stderr, stdout, fp 등 지정 가능 (FILE *)
    // printf = fprintf(stdout,...) 
    fprintf(stderr, "키는 양수로 입력해야 합니다.\n");
    return 1;
  }

  printf("몸무게(kg): ");
  fflush(stdout);
  if (scanf("%lf", &weight) != 1 || weight <= 0) {
    fprintf(stderr, "몸무게는 양의 정수로 입력해야 합니다.\n");
    return 1;
  }



  bmi = weight / (height * height / 10000);
  printf("%.fcm, %.fKg, BMI=%.2f\n", height, weight, bmi);

  return 0;
}


