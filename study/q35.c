/*
[문제35] 메뉴 프로그램
주메뉴 5개를 화면에 출력하고 각 메뉴 선택시 각 메뉴화면이 실행된 후 아무키나 입력하면 다시 주메뉴 화면으로 돌아오는 프로그램을 작성
하시오.
입력은 getchar() 함수 사용(입력버퍼의 내용을 지우 방법은 getchar() 함수를 이용하여 버퍼내의 값을 하나씩 삭제하는 코드로 작성하시오.)
1) 실행 예
--------------------
1. 입력하기
2. 출력하기
3. 검색하기
4. 삭제하기
5. 종    료
--------------------
## 메뉴 선택:  1
** 입  력 **
--------------------
1. 입력하기
2. 출력하기
3. 검색하기
4. 삭제하기
5. 종    료
--------------------
## 메뉴 선택
*/

#include <stdio.h>

void print_menu(void);
void clear_input(void);

int main(void) {

    int choice;

    do {
        print_menu();

        fflush(stdout);
        choice = getchar();
        if (choice != '\n' && choice != EOF) {
            clear_input();
        }
        printf("입력된 번호 : %c\n", choice);

    } while (choice != '5');

    return 0;
}

void print_menu(void) {
    printf("--------------------\n"
           "1. 입력하기\n"
           "2. 출력하기\n"
           "3. 검색하기\n"
           "4. 삭제하기\n"
           "5. 종    료\n"
           "--------------------\n"
           "## 메뉴 선택 : ");
}

void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
