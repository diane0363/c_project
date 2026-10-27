/*
[문제39-1] 정렬하기
- static swap 함수 추가

1차원 10개의 배열내에 1~100사이의 난수 정수를 발생시켜 초기화 한 후
버블정렬 과 교환정렬하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap(int *a, int *b);

void b_sort(int *arr, int length);
void e_sort(int *arr, int length);
void print_arr(int *arr, int length);

int main(void) {
    // 난수 시드
    srand((unsigned int)time(NULL));

    int arr[10];
    int length = sizeof(arr) / sizeof(arr[0]);

    // 버블 정렬 배열 초기화
    for (int i = 0; i < length; i++) {
        arr[i] = (rand() % 100) + 1;
    }

    print_arr(arr, length);

    b_sort(arr, length);

    print_arr(arr, length);

    // 교환 정렬 배열 초기화
    for (int i = 0; i < length; i++) {
        arr[i] = (rand() % 100) + 1;
    }

    print_arr(arr, length);

    e_sort(arr, length);

    print_arr(arr, length);

    return 0;
}

static void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// 버블 정렬 : 뒤에서부터 정렬
void b_sort(int *arr, int length) {
    while (length > 1) {
        for (int i = 0; i < length - 1; i++) {
            // 인접한 두 값 비교 후 변경
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
            }
        }
        // 정렬된 인덱스 제외
        length--;
    }
}

// 교환 정렬 : 앞에서부터 정렬
void e_sort(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        // 제일 작은 수를 찾아 현재 인덱스에 넣기
        for (int j = i + 1; j < length; j++) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
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
