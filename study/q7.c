/*
[문제7] 대학 졸업여부 확인하기
대학을 졸업하려면 최소 140학점을 이수해야 한다. 
이수한 학점 중 전공은 70학점 이상이어야 하며, 교양과 일반은 각각 30학점이거나 총점이 80학점 이상이어야 한다. 
이수한 학점을 각각 입력 받아 졸업여부를 출력하는 프로그램을 작성하시오.
1) 실행 결과
전공 이수 학점 :70
교양 이수 학점 :70
일반 이수 학점 :50
졸업가능
전공 이수 학점 :50
교양 이수 학점 :10
일반 이수 학점 :20
졸업 불가능


*/

#include <stdio.h>

int main(void)
{
  int major;
  int liberal;
  int standard;

  printf("전공 이수 학점 :");
  fflush(stdout);
  if (scanf("%d", &major) != 1 || major < 0) {
    fprintf(stderr, "0이상의 정수만 입력\n");
    return 1;
  }

  printf("교양 이수 학점 :");
  fflush(stdout);
  if (scanf("%d", &liberal) != 1 || liberal < 0) {
    fprintf(stderr, "0이상의 정수만 입력\n");
    return 1;
  }

  printf("일반 이수 학점 :");
  fflush(stdout);
  if (scanf("%d", &standard) != 1 || standard < 0) {
    fprintf(stderr, "0이상의 정수만 입력\n");
    return 1;
  }

  int total = major + liberal + standard;

  if (total >= 140 && major >= 70 && (liberal + standard >= 80 ||  (liberal >= 30 && standard >= 30))){
    printf("졸업가능\n");
  } else {
    printf("졸업 불가능\n");
  }

  return 0;
}