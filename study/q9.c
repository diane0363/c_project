/*
[문제9] 윤년/평년 판단하기
키보드로부터 연도를 입력받아 해당 연도가 윤년인지 평년인지 판단하는 프로그램 작성하시오
단, if 문을 이용해야 함
1) 공식
서력 기원 연수가 4로 나누어 떨어지는 해는 윤년이다. (1992년, 1996년, 2004년....)
서력 기원 연수가 4, 100으로 나누어 떨어지는 해는 평년이다. (1900년, 2100년....)
서력 기원 연수가 4, 100, 400으로 나누어 떨어지는 해는 윤년이다. (1600년, 2000년, 2400년)
2) 실행결과
3) test data
년도를 입력하시오 : 2010
2010년은 평년(Common year)입니다.
년도를 입력하시오 : 2004
2004년은 윤년(Leap year)입니다.
윤년 : 1600, 2000, 2008, 4, 1996
평년 : 1700, 2002, 2010, 7, 1995
*/

#include <stdio.h>

int main(void)
{
  int year;
  int is_leap = 0; // 0이면 평년, 1이면 윤년
  // char **result[] = ['평년(Common year)', '윤년(Leap year)']; - Python 문법임!!! 배열은 {}, 작은 따옴표는 문자 하나, 큰 따옴표는 문자열
  const char *result[] = {"평년(Common year)", "윤년(Leap year)"}; // 문자열을 담으니 const 꼭 써주기!!

  printf("년도를 입력하시오 : ");
  fflush(stdout);

  if (scanf("%d", &year) != 1 || year <= 0) {
    fprintf(stderr, "1이상의 정수 입력\n");
    return 1;
  };

  if (year % 4 == 0) {
    if (year % 400 == 0) { // 윤년
      is_leap = 1;
    } else if (year % 100 == 0) { // 평년
      is_leap = 0;
    } else {
      is_leap = 1;
    }
  } // 나머지는 평년

  printf("%d년은 %s입니다.\n", year, result[is_leap]);
  
  return 0;
}