const char *f1(void) { return "hello"; } 
// char* 을 반환한다 -> 정확히는 const char* 반환. h를 가리키는 포인터 반환
// hello는 .rodata에 있고, 프로그램 끝까지 살아있다. 
char *f2(void) { char s[] = "hello"; return s; } 
// 지역변수 s를 가리키는 포인터 반환. 리턴 시 s는 소멸
char *f3(void) { char *s = malloc(6); if (s) strcpy(s, "hello"); return s; } 
// malloc(6) -> sizeof(char)은 표준이 항상 1. hello\0 까지 6바이트.
// malloc(strlen(src) + 1) 이 더 올바르다. 
// if(s) 인 이유는 NULL이 아니면(메모리 할당 성공) strcpy를 하는거니? - 맞음. NULL 역참조 방지
// s는 포인터를 전달해주는 거니까. 변수 소멸 문제는 없는건가? - 맞음. 주소값을 복사해 반환하고, 해당 힙 블록은 살아있음. 
// *** 하지만 해제의 책임이 생긴다. 호출자가 free를 하지 않으면 메모리 누수. ***