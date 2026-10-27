/*
[문제39] 정렬하기
1차원 10개의 배열내에 1~100사이의 난수 정수를 발생시켜 초기화 한 후
버블정렬 과 교환정렬하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void b_sort(int *arr, int length);
void e_sort(int *arr, int length);
void print_arr(int *arr, int length);

int main(void) {
    // 난수 시드
    srand((unsigned int)time(NULL));

    int arr[10];
    int length = sizeof(arr) / sizeof(arr[0]);

    // 배열 초기화
    for (int i = 0; i < length; i++) {
        arr[i] = (rand() % 100) + 1;
    }

    print_arr(arr, length);

    // 버블 정렬 (뒤에서 부터 큰 값이 정렬된다.)
    b_sort(arr, length);

    print_arr(arr, length);

    // 교환 정렬
    // 해당 인덱스 값을 찾아 넣기
    e_sort(arr, length);

    print_arr(arr, length);

    return 0;
}

// 버블 정렬 : 뒤에서부터 정렬
void b_sort(int *arr, int length) {
    int tmp;
    while (length > 1) {
        for (int i = 0; i < length - 1; i++) {
            // 인접한 두 값 비교 후 변경
            if (arr[i] > arr[i + 1]) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        }
        // 정렬된 인덱스 제외
        length--;
    }
}

// 교환 정렬 : 앞에서부터 정렬
void e_sort(int *arr, int length) {
    int tmp;
    for (int i = 0; i < length; i++) {
        // 제일 작은 수를 찾아 현재 인덱스에 넣기
        tmp = arr[i];
        for (int j = i + 1; j < length; j++) {
            if (tmp > arr[j]) {
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

void print_arr(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}
