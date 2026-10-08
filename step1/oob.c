/*
-fsanitize=address : ASan(AddressSanitizer)
  : 실행 중 메모리 접근을 감시
  : 변수 주위에 접근 금지 구역 (redzone)을 깔아 두고 감시 

  ** 하지만 관찰 대상이 바뀔 수 있으니 주의.
    => 관찰 대상의 메모리 배치 자체를 바꾼다. 
      - shadow byte 하나는 실제 메모리 8바이트 사용
      - f1 f1 f1 f1 00 00[04]f3 f3 f3 f3 f3 f3 f3 f3 f3 (f1은 arr 앞, f3은 arr뒤 redzone)
        -> 결과의 arr프레임의 오프셋이 32인 이유 
    - 메모리 버그의 위치 -> Asan 빌드
    - 실제 메모리의 모양 -> 일반 빌드 + gdb
  
  - gcc -std=c17 -Wall -Wextra -g -fsanitize=address -o oob_asan oob.c
    ./oob_asan; echo "exit code: $?"

    *(결과 해석)
    - ERROR: AddressSanitizer: stack-buffer-overflow => 오류 종류
    - READ of size 4 at 0x7113ba9f0034 thread T0 => 접근 방식 : 4바이트 (int 하나) 를 읽었다. 
    - #0 0x5a4ba3596476 in main /home/di/c_project/oob.c:58 => 코드 위치. 
      - 콜 스택 ; 위에서부터 읽고, 처음 나오는 내 파일이 출발점) 
      - 다음(#1)부터는 libc 시작코드 
        - libc는 C표준라이브러리. prinf, scanf 등... 
    - [32, 52) 'arr' (line 13) <== Memory access at offset 52 overflows this variable => 변수 

  - gcc -std=c17 -Wall -Wextra -g -o oob_plain oob.c
    ./oob_plain; echo "exit code: $?"

    *(결과)
      sum = 15
      exit code: 0

- 공부
  1. 메모리는 항상 어떤 바이트 값을 가지고 있다.
    - java의 null이나 python의 None같은 것은 언어가 제공하는 추상화! 
    - 위의 두번째 명령에서 계속 15가 나온 이유는 다음 메모리의 4바이트가 우연히 0이었기 때문 (gdb로 확인 가능)
  2. 항상 같은 값이 나오는 이유 (미정의 동작 : Undefined Behavior)
    - 같은 실행 파일이 같은 환경에서 돌면 스택 배치도 동일 -> 같은 쓰레기 값을 읽는다. => 미정의 동작
    - 아닌 경우,
      - 변수 하나를 추가해 스택 배치 변경
      - -02로 최적화(컴파일러는 UB가 없다고 가정하고 코드 변형)
      - 컴파일러나 CPU가 다른 곳에서 실행
  3. Java라면 ArrayIndexOutofBoundsException 발생. 하지만 C는 성능을 위해 검사 X (검사의 책임은 개발자에게)

- 이해도 확인 문제 
  1. arr이 차지하는 크기가 왜 20바이트입니까?
     - int(4byte)로 5개의 값을 가지는 배열이기 때문에 ...
     => C표준은 int 크기를 "최소 16비트"라고 정함. 정확한 크기는 컴파일러와 CPU에게 위임. (자바는 어디서나 32비트 고정)
     => sizeof(int)로 항상 확인!
     => CHIP-8처럼 정확히 8,16비트가 필요한 경우, uint8_t, uint16_t 사용
  2. [32, 52)에서 오프셋 52는 arr의 몇 번째 인덱스에 해당합니까? 계산 과정을 보이십시오.
     - 32, 36, 40, 44, 48, (52) => 5번째 인덱스
     - arr[i]의 위치 = arr의 시작 + i × sizeof(int)
        52 = 32 + i × 4   →   i = 5

*/
#include <stdio.h>

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    int sum = 0;
    int i;

    for (i = 0; i <= 5; i++) {
        sum += arr[i];
    }
    printf("sum = %d\n", sum);
    return 0;
}