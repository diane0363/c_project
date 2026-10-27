/*
[문제37] 배열 뒤집기
길이가10인 정수 배열을 선언하고 임의의 값으로 초기화 시킨 후, 전체 배열의 내용을 앞 뒤를 바꿔 재배치하는 코드를 작성하시오
1)실행 예
재배치 전 출력 : 56 74 46 52 66
재배치 후 출력 : 66 52 46 74 56

*/

#include <stdio.h>
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()

int main(void) {
    // 난수 발생 초기화
    // warning: conversion from ‘time_t’ {aka ‘long int’} to ‘unsigned int’ may change value [-Wconversion]
    srand((unsigned int)time(NULL));

    int origin[10];
    int length = sizeof(origin) / sizeof(origin[0]);

    printf("재배치 전 출력 : ");

    // 배열 난수 초기화
    for (int i = 0; i < length; i++) {
        origin[i] = (rand() % 100) + 1;
        printf("%d\t", origin[i]);
    }

    // 재정렬
    int swap = 0;

    for (int i = 0; i < length / 2; i++) {
        swap = origin[i];
        origin[i] = origin[length - i - 1];
        origin[length - i - 1] = swap;
    }

    // 재배치 후 출력
    printf("\n재배치 후 출력 : ");

    for (int i = 0; i < length; i++) {
        printf("%d\t", origin[i]);
    }

    printf("\n");

    return 0;
}
