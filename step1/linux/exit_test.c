   #include <stdio.h>

   int main(void)
   {
       printf("to stdout\n");
       fprintf(stdout, "to stdout\n") 와 동일
       fprintf(stderr, "to stderr\n"); // 

    // 출력 결과 2\n134\n
       fprintf(stdout, "1");
       fprintf(stderr, "2\n");
       fprintf(stdout, "3");
       fprintf(stdout, "4\n");

       

       return 3;
   }