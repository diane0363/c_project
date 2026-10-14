// 다음 선언 각각을 “○○는 ~~을 반환하는 함수” 또는 “○○는 ~~을 가리키는 포인터” 형태의 한 문장으로 읽어 보십시오.
char *get_name(int id); // char* 을 반환하는 함수
int (*op)(int, int); // int를 반환하는 함수를 가리키는 포인터 변수
int *arr; // int를 가리키는 포인터 변수 
int **make_grid(int rows, int cols); // int를 두개 받아 int를 가리키는 포인터를 가리키는 포인터를 반환하는 함수
// + 변수를 반환하는 것 XX 변수 안의 값!을 복사해서 반환!!!

/* 1. char ***p;를 한 문장으로 읽으십시오. 
    - char을 가리키는 포인터를 가리키는 포인터를 가리키는 포인터 변수
  2. 그리고 *p, **p, ***p의 타입을 각각 쓰십시오.
    - char**, char*, char
*/

/*
0x1000 x  5
0x2000 p  0x1000
0x3000 pp 0x2000
*/

int   x  = 5;
int  *p  = &x;
int **pp = &p;

/*
x		-> int 5
&x		-> int* 0x1000
p		-> int* 0x1000
*p		-> int 5 
&p		-> int** 0x2000
pp		-> int** 0x2000
*pp		-> int* 0x1000
**pp		-> int 5 
*/