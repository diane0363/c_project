/* 두 가지 방법으로 컴파일하고 출력 비교 
- -Wall : 주요 경고 활성화 , -Wextra : 추가 경고 활성화 사용
  - gcc -std=c17 -o warn_quiet warn.c 
    -> 출력X

  - gcc -std=c17 -Wall -Wextra -o warn_loud warn.c
    -> 
      warn.c: In function ‘main’:
      warn.c:13:9: warning: suggest parentheses around assignment used as truth value [-Wparentheses]
        13 |     if (x = 5) {
            |         ^
      warn.c:11:9: warning: unused variable ‘unused’ [-Wunused-variable]
        11 |     int unused = 10;

- 의문 : if (x=5) 가 문법적으로 가능한가? 
  => 가능 (경고 없이 Compile) -> -Wall 이 있어야 경고 출력 
  - java의 경우 Compile Error (boolean제외)/ python의 경우 SyntaxError(혹은 := 사용)

  -> gcc의 규칙. 대입의 의도한 것이라면, (x)=5로 아니라면 x==5로 수정

*/

#include <stdio.h>

int main(void)
{
    int x;
    int unused = 10; 

    // 아래와 같은 문법 가능 (경고 없이 Compile) -> -Wall 이 있어야 경고 출력 
    // 대입의 의도한 것이라면, (x)=5로 아니라면 x==5로 수정
    // if (x = 5) {
    
    if (x == 5) {
        printf("x is 5\n");
    }
    return 0;
}
