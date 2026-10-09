# [Step 1] 개발 환경 구축 — Linux 기본기 정리

> 환경: Windows 10 Pro + WSL2(Ubuntu) + gcc + gdb + VS Code
> 컴파일 기본 옵션: `gcc -Wall -Wextra -g -fsanitize=address a.c -o a`

---

## 1. Linux의 기본

| 층 | 내용 | 현재 목표에서 |
|---|---|---|
| 1층: 사용자 | 파일시스템, 기본 명령어, 권한, 표준 스트림·리다이렉션, 종료 코드, PATH, apt, man | **필수** |
| 2층: 개발자 | 프로세스·시그널, fd, 시스템 콜 vs 라이브러리, 메모리 레이아웃, ELF·공유 라이브러리, make, gdb | **필수** |
| 3층: 운영 | systemd, 네트워크, ssh, 셸 스크립팅 심화, cron | 보류 |

핵심은 명령어 암기가 아니라 **"C 코드 한 줄이 OS에서 무슨 일을 일으키는가"를 연결하는 능력**.

### 주요 디렉토리

| 경로 | 내용 |
|---|---|
| `/` | 최상위. 드라이브 문자 없이 모든 것이 여기 매달림 |
| `/home/<user>` (`~`) | 내 홈 폴더 |
| `/usr/bin` | 일반 명령어 실행 파일 |
| `/usr/include` | C 헤더 파일 (`stdio.h` 등) |
| `/usr/lib` | 라이브러리 (`libc.so.6` 등) |
| `/etc` | 설정 파일 |
| `/tmp` | 임시 파일 |
| `/dev` | 장치 파일 |
| `/proc` | 커널이 노출하는 프로세스 정보 |

**WSL2 주의**: 코드는 `~/c_project`처럼 Linux 쪽에 둘 것. `/mnt/c/...`는 느리고 권한 비트가 제대로 동작하지 않음.

---

## 2. 작업 폴더 구성

```
~/c_project/
├── step1/
│   ├── gdb/
│   └── linux/
├── step2/
└── ...
```

원칙: **하나의 실습 = 하나의 폴더, 폴더 안에 `main`은 하나.**
- C는 실행 파일 하나에 `main`이 정확히 하나여야 함 (Java는 클래스마다 `main`이 있어도 됨)
- `gcc *.c` 시 `main`이 여러 개면 `multiple definition of 'main'` 링크 에러

---


## 3. PATH: `exit_test`는 안 되고 `./exit_test`는 되는 이유

- 명령어에 `/`가 **없으면** → 명령 이름으로 보고 `PATH`에 등록된 폴더만 검색. 현재 폴더(`.`)는 `PATH`에 없음
- 명령어에 `/`가 **있으면** → 경로로 보고 그 파일을 직접 실행. `./` = 현재 폴더
- Windows `cmd`는 현재 폴더를 먼저 검색하지만, Linux는 **보안상** 하지 않음 (악성 `ls` 파일 문제)

```bash
echo $PATH
which ls      # /usr/bin/ls
```

---

## 4. 종료 코드 `$?`

- `main`의 `return` 값 = 프로세스 종료 코드 (Java의 `System.exit()`에 해당)
- `$?`는 **직전 명령 하나**의 종료 코드. 모든 명령(`echo` 포함)이 종료 코드를 남기므로 매번 덮어써짐

```bash
./exit_test   # 종료 코드 3
echo $?       # 3 출력, 그리고 이 echo의 종료 코드 0이 $?에 덮어써짐
echo $?       # 0
./exit_test; rc=$?   # 나중에 쓰려면 즉시 저장
```

- 0 = 성공, 0이 아닌 값 = 실패(의미는 프로그램이 정함)

---

## 6. fd (File Descriptor)

**커널이 프로세스에게 준 "열린 파일의 번호표". 그냥 정수(int).**

```
[프로세스의 fd 표]  ← 커널이 관리
 fd 0 → stdin  (키보드)
 fd 1 → stdout (터미널)
 fd 2 → stderr (터미널)
 fd 3 → 이후 새로 연 파일부터 배정
```

- 모든 프로세스는 시작 시 0, 1, 2가 이미 열려 있음
- Java/Python은 스트림 **객체**를 주지만 내부적으로는 이 정수를 들고 있음. C는 정수를 직접 다룸

| | Java | Python | C/Linux |
|---|---|---|---|
| 표준 출력 | `System.out` | `sys.stdout` | fd 1 |
| 표준 에러 | `System.err` | `sys.stderr` | fd 2 |

---

## 7. 리다이렉션

| 기호 | 의미 |
|---|---|
| `> file` | stdout을 파일로 (덮어쓰기). `1> file`의 줄임 |
| `>> file` | stdout을 파일 끝에 추가 |
| `2> file` | stderr를 파일로 |
| `2>&1` | fd 2를 **fd 1이 지금 가리키는 곳**으로 복사 |
| `cmd1 \| cmd2` | cmd1의 stdout을 cmd2의 stdin으로 |

- `&1`의 `&` = "파일 이름이 아니라 fd 번호". `2>1`은 `1`이라는 **파일**을 만듦
- 리다이렉션은 **셸이 프로그램 실행 전에, 왼쪽→오른쪽 순서로** 처리
  - 그래서 실행이 Permission denied로 실패해도 `> test.txt`의 빈 파일은 생성됨

### 순서에 따른 차이 (Java 참조 대입과 동일)

```java
// ./exit_test > out.txt 2>&1
fd1 = outFile;
fd2 = fd1;        // fd2 = outFile

// ./exit_test 2>&1 > out.txt
fd2 = fd1;        // fd2 = terminal (그 시점의 fd1)
fd1 = outFile;    // fd2는 영향 없음
```

| 명령 | stdout | stderr |
|---|---|---|
| `./exit_test > out.txt 2>&1` | 파일 | 파일 |
| `./exit_test 2>&1 > out.txt` | 파일 | **화면** |
| `./exit_test 2> err.txt > out.txt` | out.txt | err.txt (화면엔 아무것도 없음) |

---

## 8. printf vs fprintf

```c
printf("x\n");               // = fprintf(stdout, "x\n")
fprintf(stderr, "err\n");    // 출력 대상을 첫 인자로 지정
```

| C | Java | Python |
|---|---|---|
| `printf("x")` | `System.out.print("x")` | `print("x")` |
| `fprintf(stderr, "x")` | `System.err.print("x")` | `print("x", file=sys.stderr)` |

- `stdout`, `stderr`는 C 라이브러리의 `FILE*`. 각각 fd 1, fd 2를 감싼 포장(버퍼 포함)
- stderr를 분리하는 이유: 정상 결과와 에러를 분리. `./prog > result.txt` 해도 에러는 화면에 보임

---

## 9. printf와 write의 관계

```
printf("...")          섹션 3: C 라이브러리 (사용자 공간)
   │  포맷팅 + 버퍼에 쌓기
   ▼
write(1, buf, n)       섹션 2: 시스템 콜
   │
   ▼
커널                    실제로 터미널/파일에 기록
```

- 시스템 콜은 커널 전환이 필요한 **비싼 연산** → 그래서 printf는 버퍼에 모아서 한 번에 write
- Java `System.out.println`, Python `print`도 Linux에서는 결국 `write`에 도달

---

## 10. 버퍼링 규칙 (중요)

| 스트림 | 연결 대상 | 버퍼링 | write 시점 |
|---|---|---|---|
| stdout | 터미널 | line buffered | `\n`을 만날 때 |
| stdout | 파일·파이프 | **fully buffered** | 버퍼가 차거나 프로그램 종료 시 |
| stderr | 어디든 | unbuffered | 즉시 |

**연결 대상에 따라 stdout의 버퍼링이 바뀜.**

`./exit_test > all.txt 2>&1` 결과가 `to stderr` → `to stdout` 순서인 이유:
1. stdout이 파일에 연결 → fully buffered → `printf`는 버퍼에만 쌓임
2. stderr는 즉시 `write(2, ...)` → 파일에 먼저 기록
3. 프로그램 종료 시 stdout 버퍼 flush → `write(1, ...)` → 나중에 기록

---

## 11. man (공식 설명서)

```bash
man ls
```
조작: `Space` 다음, `b` 이전, `/단어` 검색, `n` 다음 결과, `q` 종료

| 섹션 | 내용 | 예시 |
|---|---|---|
| 1 | 셸 명령어 | `man 1 ls` |
| 2 | 시스템 콜 | `man 2 write` |
| 3 | C 라이브러리 함수 | `man 3 printf` |

- **함정**: `man printf`는 섹션 1(셸 명령어 printf)이 나옴. C 함수는 반드시 `man 3 printf`
- 설명서가 없으면: `sudo apt install man-db manpages-dev`

---

## 12. 실행 파일 분석 (file, ldd)

```
exit_test: ELF 64-bit LSB pie executable, x86-64, dynamically linked,
interpreter /lib64/ld-linux-x86-64.so.2, with debug_info, not stripped
```

- `ELF`: Linux 실행 파일 형식 (Windows `.exe`는 PE 형식)
- `dynamically linked`: `printf` 등의 실제 코드는 실행 시점에 외부 라이브러리에서 불러옴
- `with debug_info, not stripped`: `-g` 옵션 덕분 → gdb가 소스 줄 번호를 앎

`ldd` 결과:
- `libc.so.6`: C 표준 라이브러리 (`printf` 실제 구현)
- `libasan.so.8`: `-fsanitize=address`의 메모리 검사 라이브러리 (`libm`, `libgcc_s`는 주로 이것의 의존성)
- `ld-linux-x86-64.so.2`: 라이브러리를 메모리에 올리는 동적 로더
- `linux-vdso.so.1`: 커널이 제공하는 가상 라이브러리
- 괄호 안 주소는 실행마다 바뀜 → ASLR (Step 3에서 다룸)

---

## 13. 권한

```
-rwxr-xr-x 1 di di 27608 Oct  9 12:00 exit_test
 │└┬┘└┬┘└┬┘
 │ │  │  └ 기타 사용자
 │ │  └─── 그룹
 │ └────── 소유자
 └──────── 파일 종류 (- 일반 파일, d 폴더)
```
r=읽기, w=쓰기, x=실행

- Python/Java는 인터프리터·JVM이 파일을 **읽어서** 실행 → 실행 비트 불필요
- gcc 결과물은 **커널이 직접 실행**하는 기계어 → 실행 비트(x) 없으면 `Permission denied`

---

## 14. 명령어 정리 (★ = 커리큘럼 필수)

### 명령어가 있는 곳
| 디렉토리 | 내용 |
|---|---|
| `/usr/bin` | 일반 명령어 대부분 |
| `/usr/sbin` | 관리자용 |
| `/usr/local/bin` | 직접 설치한 프로그램 |
| `/bin`, `/sbin` | 최신 Ubuntu에서는 `/usr/...`로의 바로가기 |

### 이동·탐색
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `pwd` | 현재 위치 | `pwd` |
| ★ `cd` | 이동 | `cd ~/c_project`, `cd ..`, `cd -` |
| ★ `ls` | 목록 | `ls -la` |
| `tree` | 트리 구조 | `tree ~/c_project` |

### 파일·폴더 조작
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `mkdir` | 폴더 생성 | `mkdir -p a/b/c` |
| `touch` | 빈 파일 생성 | `touch main.c` |
| ★ `cp` | 복사 | `cp a.c b.c`, `cp -r d1 d2` |
| ★ `mv` | 이동·이름 변경 | `mv old.c new.c` |
| ★ `rm` | 삭제 (복구 불가) | `rm a.out`, `rm -r dir` |

### 내용 보기
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `cat` | 전체 출력 | `cat out.txt` |
| `less` | 페이지 단위 (`q` 종료) | `less big.log` |
| `head` / `tail` | 앞/뒤 일부 | `tail -n 8 file` |
| `xxd` | 바이너리를 16진수로 | `xxd game.ch8` (CHIP-8 ROM 분석) |

### 검색
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `grep` | 내용 검색 | `grep -rn "main" .` |
| `find` | 이름 검색 | `find . -name "*.c"` |
| `which` | 명령어 위치 | `which gcc` |

### 권한
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `chmod` | 권한 변경 | `chmod +x prog` |
| `sudo` | 관리자 권한 실행 | `sudo apt install ...` |

### 프로세스
| 명령어 | 기능 | 예시 |
|---|---|---|
| `ps` | 프로세스 목록 | `ps aux` |
| `top` | 실시간 모니터 (`q` 종료) | `top` |
| `kill` | 시그널 보내기 | `kill 1234` |
| `Ctrl+C` | 실행 중 프로그램 종료 | 무한 루프 탈출 |

### 셸 기호
| 기호 | 의미 |
|---|---|
| ★ `>` / `>>` | stdout 덮어쓰기 / 추가 |
| ★ `2>` | stderr를 파일로 |
| ★ `2>&1` | stderr를 stdout이 가는 곳으로 |
| `\|` | 파이프 |
| ★ `$?` | 직전 명령 종료 코드 |
| `~`, `.`, `..` | 홈 / 현재 / 상위 폴더 |

### 패키지·도움말
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `apt` | 설치 | `sudo apt update`, `sudo apt install gdb` |
| ★ `man` | 설명서 | `man 3 printf` |
| `--help` | 간단 도움말 | `ls --help` |

### C 개발 도구
| 명령어 | 기능 | 예시 |
|---|---|---|
| ★ `gcc` | 컴파일 | `gcc -Wall -Wextra -g -fsanitize=address a.c -o a` |
| ★ `gdb` | 디버거 | `gdb ./a` |
| `file` | 파일 종류 | `file a` |
| `ldd` | 공유 라이브러리 | `ldd a` |
| `strace` | 시스템 콜 추적 | `strace ./a` |
| `make` | 빌드 자동화 | `make` |

---

## 15. 실수 기록 (다시 하지 말 것)

- `gcc` 직후 `echo $?` → gcc의 종료 코드(0)를 본 것. 프로그램 **실행 직후**에 확인해야 함
- 실습 출력 파일을 `cat`으로 확인하지 않음 → 확인하지 않은 것은 확인한 것이 아님
- "PATH 문제"를 "루트를 `/`로 탄다"로 잘못 이해함
- "stdout은 line buffered"라고 단정 → 연결 대상이 파일이면 fully buffered
- 관찰 결과의 이상 현상(출력 순서 역전)을 그냥 넘김 → 이상 현상이 곧 학습 포인트

