/*
- 파일 실행 / 종료코드 출력 / 
  - gcc -std=c17 -Wall -Wextra -g -fsanitize=address -o hello hello.c

  - ./hello; echo "exit code: $?"
    *(Linux 사용 시 디렉터리)
      - Linux는 보안상 현재 디렉터리를 PATH에 넣지 않음. 꼭 ./ 필수 기입! 
    *(bash 문법) 
      - A ; B : A의 성패여부 상관없이 B 실행
      - A && B : A의 exit code가 0일 때만 B 실행 

  - head -c 4 hello | od -c
    *(od -c 출력 결과)
      0000000 177   E   L   F
      0000004
    *(해석)
      0000000 : 이 줄의 첫 바이트가 파일의 몇 번 째 바이트인가(오프셋) ; od는 기본적으로 8진수 표시
      177   E   L   F : 4바이트의 내용 (-c 는 문자 표시 옵션. 출력 불가 바이트는 8진수 표시)
        => 177은 10진수로 127, 16진수로는 0x7F
      0000004 : 데이터의 끝 오프셋 (총 4바이트 읽음!)
    => ELF 매직 넘버 (Windows의 MZ에 해당하는 Linux쪽 표식)
*/

#include <stdio.h>

int main(void)
{
    printf("Hello, CHIP-8\n");
    return 0;
    // 종료 코드 출력 echo "exit: $?" -> $에 0!
}