```bash
gcc -Wall -Wextra -Wconversion -std=c17 -g -fsanitize=address -o main main.c && ./main
./out                 # 두 줄 모두 화면에 보임
./out > result.txt    # 화면에는 "에러 메시지"만 보임
cat result.txt        # "정상 결과"만 들어 있음
./out 2> err.txt      # 화면에는 "정상 결과"만, err.txt에는 "에러 메시지"

gdb -q ./main

(gdb)
# gdb와 LeakSanitizer가 같은 프로세스를 동시에 ptrace하려다가 충돌 -> LSan의 오류로 exit(1)
# LSan이 clone()으로 tracer 자식 생성 (fork)
[Detaching after fork from child process 74775]
==74676==LeakSanitizer has encountered a fatal error.
==74676==HINT: For debugging, try setting environment variable LSAN_OPTIONS=verbosity=1:log_threads=1
==74676==HINT: LeakSanitizer does not work under ptrace (strace, gdb, etc)
[Inferior 1 (process 74676) exited with code 01]

```
```c
#include <stdio.h>

int main(void)
{

  return 0;
}

```
## 0-1. %d, &a
  - % : 주소값으로 인식한다. -> 값을 넘겨도 해당 값을 주소로 인식
    - %d : (정수)
      - 공백 문자 건너 뛴다 -> 부호를 읽는다. -> 숫자를 읽을 수 있을 만큼 읽는다. -> 버퍼에 문자가 있는 경우, 해당 문자들은 버퍼에 되돌려 놓는다.
      - ******** 12abc가 입력값으로 들어간 경우, 값은 12, 반환값은 1, abc는 버퍼에 남는다 ***********
  - &a : a 변수의 주소 값을 가진다.

## 3-1. %lf, %f
  - %f : float비트 패턴 4바이트 -> double을 담으면 앞 4바이트(리틀 엔디언)만 덮어씀
  - %lf : 8바이트
  - 출력 시에는 가변 인자 규칙에 따라 float을 넘겨도 double로 자동 승격이 된다.
  - 입력 시에는 해당 주소에 4바이트를 쓸 지, 8바이트를 쓸 지 알아야하므로 미리 지정해두어야한다!!!

## 3-2. 리틀 엔디언
  - 8바이트, x86은 리틀 엔디언이라 하위 바이트가 앞 주소
  -

## 4-1. const로 상수 변수 선언
  - 무조건 선언과 할당 동시에!!
  ```c
  const double PI = 3.141592;
  PI = 3.14; // 컴파일 에러
  ```

## 4-2. const vs #define
  - const : 컴파일러가 처리, double타입, 블록 스코프
  - #define : 컴파일 전 전처리기가 텍스트 치환, 데이터 타입 없음(치환된 리터럴 타입 따름), 전역 스코프, gdb에서 print PI 안 뜸

## 4-3. 곱셈 순서와 타입 변환 시점
  ```c
  int r = 12;

  r * r * PI // int 연산 -> double 연산 (signed overflow 발생 가능성 고려 -> wrap-around가 아닌 미정의 동작 (UB) 발생)
  PI * r * r // double 연상 -> double 연산
  ```

## 5-1. 산술 연산자
  - +, -, * : signed overflow -> UB 주의
  - / : 몫 (소수점 버림) ; 0으로 나누면 UB
  - % : 나머지 ; 정수 전용. double에 쓰면 컴파일 에러 (실수는 fmod()) ;; python, Java는 가능

## 5-2. 음수 나눗셈
  - 7 / 2 = 3
  - -7 / 2 = -3 ***(python : -4)
  - -7 % 2 = -1 ***(python : 1)

## 5-3. 돈은 정수로
  - 이진 부동소수점 -> 0.1을 정확하게 표현 X => double로 계산 시 누적 오차 발생
  - 기본적으로 int, 큰 금액 계산 시 long long(최소 64비트 보장, %lld)

## 5-4. %d 에 담는 버퍼에 문자가 있는 경우
  - %d : (정수)
    - 공백 문자 건너 뛴다 -> 부호를 읽는다. -> 숫자를 읽을 수 있을 만큼 읽는다. -> 버퍼에 문자가 있는 경우, 해당 문자들은 버퍼에 되돌려 놓는다.
    - ******** 12abc가 입력값으로 들어간 경우, 값은 12, 반환값은 1, abc는 버퍼에 남는다 ***********

## 5-5. putchar(c) & getchar()
  - putchar(c) : stdout에 문자 1개 쓰기 | Python의 print(c, end='')
  - getchar() : stdin에서 문자 1개 읽기 | Python의 sys.stdin.read(1)
  ```c
  putchar('A'); // printf("%c", 'A')와 같은 결과
  ```

## 7-1. 관계 연산자와 논리 연산자
  - >=, &&, ||, !

## 7-2. C에는 boolean이 없다.
  - C99부터 <stdbool.h>를 포함하면 bool, true, false 사용 가능.
  - 내부적으로는 여전히 0과 1

## 7-3. 연산식 우선 순위

## 7-4. if (x = 70) {}
  - 가능

## 7-5. 범위 검사 X<=Y && Y<=Z (X<=Y<=Z 불가능)
  - X<=Y<=Z -> X <= Y 를 비교한 결과 0, 1 을 가지고 Z와 비교 (왼쪽부터 하나씩)

## 8-1. /, % 연산자
  ```c
  456 % 10 = 6
  456 / 10 = 45
  ```

## 8-2. /, %, * - 연산자 우선순위 동일

## 9-0. 체크하기
  ```c
    char **result[] = ['평년(Common year)', '윤년(Leap year)']; // Python 문법임!!! 배열은 {}, 작은 따옴표는 문자 하나, 큰 따옴표는 문자열
    const char *result[] = {"평년(Common year)", "윤년(Leap year)"}; // 문자열을 담으니 const 꼭 써주기!!
  ```
## 9-1. if / else if
  - else if 에서의 조건 검사 순서. -> 구체적인 예외를 먼저 작성해야한다. (순서대로 검사하기 때문)
  - java의 경우, 데드코드를 알려주지만, C는 알려주지 않는다.


## 10-1. scanf(형식문자열, 결과를 쓸 위치1, ...)
  - stdin에서 입력을 읽어, 형식문자열의 지정자에 따라 변환 후, 결과를 2번째 이후 인자들이 가리키는 주소에 순서대로 쓴다.
  - 형식문자열의 %지정자를 하나 읽을 때마다, 다음 인자를 그 타입의 포인터라고 !!믿고!! 꺼낸다.
  - 가변 인자 함수라 실행 중에 실제 타입 확인 X -> 해당 바이트만큼 읽고 쓴다. (-Wall 로 경고)
    - %d -> 다음 인자를 int * 로 간주
    - %lf -> 다음 인자를 double * 로 간주
    - %c -> 다음 인자를 char * 로 간주

  ```c
    int n1;
    int *p = &n1;
    scanf("%d", p);     // O : n1변수 자체를 덮어씀
    scanf("%d", &p);    // X : p변수 자체를 덮어씀
  ```

## 10-2. 関数 ー 返す；void, int
  ‐ return : 중간에 빠져나갈 때만 사용

## 11-1. n % 0 -> 단락 평가로 막기
  - python, Java 모두 예외로 뜨지만
  - C는 미정의 동작. x86 Linux에서는 보통 SIGFPE로 프로그램 종료
  ```c
    b != 0 && n % b == 0     /* ✅ b가 0이면 여기서 멈춤. % 연산 안 함 */
    n % b == 0 && b != 0     /* ❌ % 를 먼저 계산 → b가 0이면 이미 UB */
  ```
  - n % -1 도 마찬가지.
    - %는 내부적으로 몫도 함께 계산
    ```c
    -2147483648 / -1 = 2147483648 // signed overflow (-> SIGFPE)
    ```

## 11-2. 삼항 연산자
  - COND ? TRUE 값 : FALSE 값

## 11-3. #include <limits.h>     /* INT_MIN */

## 11-4. #include <stdbool.h>    /* bool, true, false */
  - int 0, 1로도 구분 가능하지만 bool을 쓰는 이유
    1. 가독성: 의도를 드러낸다.
    2. 동작의 차이: 0이 아닌 값은 모두 1로 바꾼다.
  - 정수 타입의 일종 : 산술 가능 (Java보다는 Python과 가깝다.)
    - java : int 와 섞으면 컴파일 에러

## 12-0. step6 비트 연산자

  #### 비트 연산자 6개

    | 연산자 | 이름 | 하는 일 | 예 (8비트) | CHIP-8에서 쓰는 곳 |
    | --- | --- | --- | --- | --- |
    | `&` | AND | 마스크로 **원하는 비트만 남김** | `1011 0110 & 0000 1111 = 0000 0110` | 명령어에서 특정 자리 추출 |
    | `|` | OR | 특정 비트를 **1로 켬** | `1011 0000 | 0000 0101 = 1011 0101` | 두 바이트를 합쳐 명령어 만들기 |
    | `^` | XOR | 특정 비트를 **뒤집음** | `1011 0110 ^ 0000 1111 = 1011 1001` | 화면 그리기 (`DXYN`) |
    | `~` | NOT | 모든 비트를 **반전** | `~1011 0110 = 0100 1001` | 마스크 만들기 |
    | `<<` | 왼쪽 시프트 | 비트를 왼쪽으로 밀고 오른쪽을 0으로 채움 | `0000 0011 << 2 = 0000 1100` | 바이트를 상위 자리로 이동 |
    | `>>` | 오른쪽 시프트 | 비트를 오른쪽으로 밀기 | `1100 0000 >> 4 = 0000 1100` | 추출한 자리를 맨 아래로 내리기 |

    `<< 1`은 곱하기 2, `>> 1`은 나누기 2와 같습니다(양수일 때).

## 12-1. 정수의 이진 표현과 최하위 비트 (LSB)
  - 짝수와 홀수는 마지막 비트로 결정

## 12-2. 비트 & 와 마스크
  - & 는 두 수를 같은 자리 비트끼리 AND
  - 1 & 1 일 때만 1
  - 비트 CLEAR 연산자 : 1 & N 은 무조건 1 (마지막 제외 모든 비트 0) -> 비트 마스크 (0000 0001)
  - 16진수 에서는 0x000F (마지막 한자리 추출)

## 12-3. &는 ==보다 우선순위가 낮다.
  ```C
  // 아래의 두 표현식이 같다. => 조건이 항상 거짓!!!
  if (n & 1 == 0)
  if (n & (1 == 0))

  // 이렇게 써주기!!!
  if ((n & 1) == 0)
  ```

## 12-4. 음수와 2의 보수
  - 음수는 2의 보수로 표현
  - 양수의 비트를 전부 뒤집고 +1

  ```
  7 = 0000 0111
  반전 1111 1000
  +1  1111 1001 = -7    ← 마지막 비트 1 → 홀수
  ```

## 12-5. C에서 &의 세 가지 의미

## 12-6. 비트 직접 보기
  - C23 부터 printf에 이진수 서식 추가 (%b)
  - gdb로 보는 법
  '''bash
    gdb ./parity
    (gdb) b main
    (gdb) r
    (gdb) n          # scanf까지 진행하며 -7 입력
    (gdb) print/t n     # /t = 이진수로 출력
    (gdb) print/x n     # /x = 16진수로 출력
  '''

## 13.
  - gdb를 이용해 디버깅 시도 -> 원인 체크 후 수정

#### gdb 명령문 추가

  | 명령 | 하는 일 |
  | --- | --- |
  | `display 変数` | 매번 멈출 때마다 `変数` 값을 자동으로 출력 (`info locals`를 반복할 필요 없음) |
  | `watch 変数` | `変数`의 값이 바뀌는 순간 자동으로 멈춤 |
  | `p 変数` | 변수 하나만 출력 (`print`의 줄임) |
  | `c` | 다음 브레이크포인트까지 계속 실행 |
  | `bt` | 함수 호출 경로 출력 (함수가 여러 개일 때) |

## 19-1. 문자 상수 'a' 와 문자열 리터럴 "a"
  ```c

    // 문자 상수 'a' 와 문자열 리터럴 "a" 항상 구분하기!!!!
    // 리터럴은 수정하면 UB -> 항상 const!!
    const char t = 'a';
    // const char t1 = "a"; /* 불가능 :['a']['\0'] 두 바이트 배열 생성 */
    const char *t3 = "ab";

    printf("%c\n", t);       /* a : 해당 문자 'a' 읽음 */
    printf(" %c\n", t);       /* whitespace를 건너뛴 뒤 첫 문자 */
    printf("%d\n", t);       /* 97 : 숫자로 저장 */
    printf("%d\n", t + 1);   /* 숫자로 저장되어있어 1을 더한 98 출력 */
    printf("%c\n", *t3);     /* a : 1바이트만 읽음 */
    printf("%c\n", *t3 + 1); /* b : 다음 바이트 */
    printf("%s\n", t3);      /* ab : 주소를 받아 \0을 만날 때까지 출력 */
    printf("%d\n", *t3);     /* 97 : 첫 바이트를 정수로 출력 */
    printf("%c\n", t ^ 0x20) /* A : 97 ^ 0x20 -> 65 => A */
  ```

## 19-2. 비트로 알파벳 대소문자 변경

  ```
  'A' = 0100 0001     'a' = 0110 0001
  'Z' = 0101 1010     'z' = 0111 1010
          ↑                    ↑
        bit 5 = 0            bit 5 = 1
  ```

  대문자와 소문자는 5번 비트 하나만 다름(2⁵ = 32 = `0x20`)

  ```c
  c ^ 0x20     /* 5번 비트 뒤집기: 대소문자 토글 */
  c | 0x20     /* 5번 비트 켜기: 소문자로 */
  c & ~0x20    /* 5번 비트 끄기: 대문자로 */
  ```

## char의 부호는 플랫폼 별 상이
  - x86 / x86-64 : 부호 있음 (-128 ~ 127)
  - ARM (STM32, 라즈베리파이 등) : 부호 없음 (0 ~ 255)

## 19-3. <ctype.h>, unsigned char

  ```c
  #include <ctype.h>

  isalpha(c)   /* 알파벳이면 0이 아닌 값 */
  isupper(c)   /* 대문자 */
  islower(c)   /* 소문자 */
  toupper(c)   /* 대문자로 변환 (알파벳이 아니면 그대로) */
  tolower(c)
  ```

  - 하지만, 인자가 `unsigned char` 범위(0~255)의 값이거나 `EOF`여야한다.
  - 이 외의 값을 넣으면, UB.
  - 그런데 x86 Linux에서 char은 부호가 있는 타입! =>  (-128 ~ 127)
  - (unsigned char) 를 앞에 명시해주기~

  ```c
  char c = '\xEA';     /* 한글 '가'의 첫 바이트 */
  isalpha(c);          /* isalpha(-22) → UB */
  isalpha((unsigned char)c);   /* isalpha(234) → 0 */
  ```

## 22. switch ~ case
  ```c
  switch (정수식) {
  case 상수1:
      /* 정수식 == 상수1 일 때 */
      break;
  case 상수2:
  case 상수3:
      /* 상수2 또는 상수3 일 때 (여러 case를 한 곳으로) */
      break;
  default:
      /* 어느 case에도 해당하지 않을 때 */
      break;
  }
  ```

## 22-1. break 주의

  ```c
  switch (n) {
  case 1:
      printf("1\n");      /* break 없음 */
  case 2:
      printf("2\n");
      break;
  }
  /* n == 1 이면 "1", "2" 둘 다 출력 */
  ```

## 22-2. case 라벨은 정수 상수식만
  ```c
  // 가능
  case 5:          /* 정수 리터럴 */
  case 'A':        /* 문자 상수도 정수 */
  case RED:        /* enum 상수 */

  // 불가능
  case x:          /* 변수 */
  case 1.5:        /* 실수 */
  case "소":       /* 문자열 */
  ```

## 22-3. case안에서 변수 선언 시 중괄호
  ```c
  case 1: {
      int tmp = 10;
      ...
      break;
  }
  ```

## 22-4. Null 이 될 수 있는 포인터는 쓰기 전에 검사한다.
  - %s는 주소를 따라가 '\0'이 나올 때까지 읽는다.
  - NULL은 0번지 -> 따라갈 곳이 없다.
  - glibc의 printf는 (null) 을 출력하도록 방어 코드가 들어가있지만,
  - 표준상 미정의 동작 -> 다른 C라이브러리에서는 크래시.

## 23-1. 값 할당 전 비교 검사하지 않기!!!
  ```c
  int x;
  int y = 0;

  // x값을 할당하지 않으면, 쓰레기값이 담겨 실행할 때마다 결과가 바뀐다.
  if (x>y) {
    ...
  }
  ```

## 23-2. for문..

## 25-1. debugging
  ```c
  //방법 1
    for (int i = 2; i <= num; i++) {
        // i가 소수인지 체크
        for (int j = 2; j <= i; j++) {
            if (i % j == 0 && i != j) {
                break; // i가 소수가 아니면 break
            }
            // 본인과 나눌 때까지도 break 되지 않았다면 소수 카운트
            if (i == j) {
                pr_cnt += 1;
            }
        }
    }
  ```

  ```c
  // 방법2 & 디버깅 결과
      for (int i = 2; i <= num; i++) {
          pr_flag = true;
          for (int j = 2; j * j <= num; j++) { // line 35
              if (i % j == 0) {
                  pr_flag = false;
                  break;
              }
          }
          if (pr_flag == true) {
              pr_cnt++;
          }
      }
  ```

  ** 문제 1 **
  ```bash
  (gdb) i lo
  j = 2
  i = 2
  num = 11
  pr_flag = true
  pr_cnt = 0
  ```
  ** 문제 2 **
  ```bash
  (gdb) b 35
  Breakpoint 1 at 0x1415: file main.c, line 35.
  (gdb) r
  Starting program: /home/di/c_project/study/main
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
  정수 입력: 2
  2~2까지 소수의 개수는 1개입니다
  [Detaching after fork from child process 28832]
  ==28818==LeakSanitizer has encountered a fatal error.
  ==28818==HINT: For debugging, try setting environment variable LSAN_OPTIONS=verbosity=1:log_threads=1
  ==28818==HINT: LeakSanitizer does not work under ptrace (strace, gdb, etc)
  [Inferior 1 (process 28818) exited with code 01]
  -----------------------------------------------------------------------------
  (gdb) b 35
  Note: breakpoint 1 also set at pc 0x555555555415.
  Breakpoint 2 at 0x555555555415: file main.c, line 35.
  (gdb) r
  Starting program: /home/di/c_project/study/main
  [Thread debugging using libthread_db enabled]
  Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
  정수 입력: 3
  2~3까지 소수의 개수는 2개입니다
  [Detaching after fork from child process 29637]
  ==29625==LeakSanitizer has encountered a fatal error.
  ==29625==HINT: For debugging, try setting environment variable LSAN_OPTIONS=verbosity=1:log_threads=1
  ==29625==HINT: LeakSanitizer does not work under ptrace (strace, gdb, etc)
  [Inferior 1 (process 29625) exited with code 01]
  */

  ```

## 26-1. 초기식
```c
    int start = 'A';
    int end = 'Z';
    //1. 초기식 start는 아무것도 하지 않는다.
    for (start; start <= end; start++) {...}
    //2. 비워두는 것이 좋다.
    for (; start <= end; start++) {...}
    // UB에 도달할 때까지 반복
    for (start; start < (start + 26); start++) {...}
```

## 26-2. 비트 연산
- 비트 연산 : ^ (비트 스위치?)
- 알파벳 : 32 차이 (A:65, a:97), A~Z 26 (Z:90)
    - => 0010 0000 (2^5)

## 27-1.

| 입력 | 기존 방식 반복 횟수 | √n 방식 반복 횟수 |
| --- | --- | --- |
| 14 | 14 | 약 6 |
| 2,000,000,000 | 20억 | 약 9만 |

## 28. 반복문 변수에서 반복 변수를 직접 바꾸지 X
- ()부분만 보면 알 수 있는 반복문의 장점을 깨뜨림
```c
    for (int n2 = 1; n2 <= 9; n2++) {
        printf("%d x %d = %d\n", n1, n2, n1 * n2);
        if (n2 == 9 && n1 < 9) {
            // n2 = 1;
            n2 = 0;
            n1++;
        }
    }
```

## 32-1. 배열 인덱싱, 슬라이싱
  - 함수는 배열이 아니라, 포인터를 받는다.
  - 포인터에는 길이 정보 X
  ---------------------------------
  - 인덱싱은 지원O (JAVA O, PY O)
  - 범위 밖 접근검사 지원X (JAVA O, PY O)
  - 슬라이싱 지원X (JAVA X, PY O)
  - SUM() 지원X (JAVA O, PY O)

## 32-2. const, static
- const 는 바로 왼쪽에 있는 것을 고정. 왼쪽에 아무것도 없다면 오른쪽을 고정
  ```c
  const char *weekdays[] = {"월요일", "화요일"};

  weekdays[0][0] = "수요일" // 컴파일 에러 (배열 값 변경하기 - 불가)
  weekdays[0] = "수요일" // 허용. (배열에 다른 주소 넣기)
  ```

  ```c
  const char *const weekdays[] = {"월요일", "화요일"};
  // 배열 포인터 변경 X, 배열 값 변경X..

  ```
- static
  - Java의 static과는 다르다.
  - 위치에 따라 달라짐
    1. 스택이 아닌 정적 영역에 저장
      - Data/Static Area : 프로그램 시작 시 크기 고정 -> 종료까지 유지
      - Heap : 실행 중 사용자가 직접 크기를 결정해 동적으로 할당 & 해제 (new, malloc)
      - Stack : 함수가 호출될 때 생성되는 지역 변수, 매개 변수 저장 (함수 실행 중에만)

      | **구분** | **정적 영역 (Static)** | **힙 영역 (Heap)** | **스택 영역 (Stack)** |
      | --- | --- | --- | --- |
      | **저장 변수** | 전역 변수, static 변수 | 동적 할당 변수 (`new`, `malloc`) | 지역 변수, 매개 변수 |
      | **할당/해제** | 프로그램 시작 시 / 종료 시 | 개발자가 원할 때 (수동/GC) | 함수 시작 시 / 함수 종료 시 |
      | **메모리 크기** | 고정됨 | 크고 유연함 (RAM이 허용하는 한) | 작고 제한적임 (보통 수 MB) |
      | **접근 속도** | 빠름 | 느림 (포인터 참조 필요) | **매우 빠름** |

    2. 함수 밖(파일 최상위)
      - 보이는 범위 변경
      ```c
      static int helper_count = 0;           /* 이 .c 파일 안에서만 보임 */
      static bool is_leap_year(int year);    /* 이 .c 파일 안에서만 호출 가능 */
      ```

## 33-1. int의 오버플로우는 UB / double의 오버플로우는 inf

## 33-2. int × int는 반드시 long long에 들어간다
  - int : 32비트, long long : 63비트
  - int x int : 어떤 경우에도 long long의 범위를 넘지 않는다. => 오버플로우 X

## 33-3. 반복해서 곱하는 대신, 지수를 이진수로 보고 제곱 -> log₂(exp) 번 반복 Wow
  ```c
  while (exp > 0) {
      if (exp & 1) {          /* 지수의 최하위 비트가 1이면 */
          result *= base;     /* 현재 base를 결과에 곱함 */
      }
      base *= base;           /* base를 제곱: 3 → 3² → 3⁴ → 3⁸ */
      exp >>= 1;              /* 지수를 오른쪽으로 한 비트 */
  }
  ```

## 33-4. assert vs if
  - 사용자의 입력 검증 : if
  - 코드 검증 : assert

## 33-5. goto
  - 해당 라벨로 이동 (like switch case:)
  ```c
  goto LABEL;

  LABEL:
    fprintf(stderr, "어쩌고");
    exit(1);
    // exit보다는 bool과 포인터를 이용해 전달하는 방법이 더 좋다.
  ```

## 35-1. getchar()의 반환 값은 int (EOF)
  - 문자값을 정수로 반환한다.
  - 문자 하나(0~255) 반환 후 더 읽을 게 없으면 EOF(-1) 반환
  ```c
  int c = getchar();
  ```

## 35-2. 입력버퍼의 남은 값들 비우기
  - '\n' : "해당 줄을 모두 소비했다"
  - 사용자가 엔터만 누른 상태'\n'에서 버퍼를 비우면, 다음에 입력될 줄을 비우게 된다.
  -

## 35-3. do ~ while
  ```c
  do {
    /* 최소 한번은 실행 */
  } while (cond); /* 세미콜론 필수! */
  ```

## 36-1. 재귀 함수

## 36-2. debugging
  - info b : 현재 걸린 bf 리스트
  - delete num : bf 리스트에서 #n bf 삭제
  - bt (backtrace) : 현재 쌓여있는 호출 (stack)
  - 호출자(d9b0) > 자신(d980) > 피호출자(d950): 스택은 낮은 주소 방향으로
  - 프레임 사이 간격은 0x30 = 48바이트

## 36-3. 누적 재귀함수 (36_1.c)

## 36-4. C에서의 static 함수
  - 함수를 해당 파일 안에서만 보이게 하는 키워드 (내부 구현용 함수에 붙인다.) -> Java의 private와 비슷한 역할

