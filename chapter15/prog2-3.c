// prog2-3.c
#include <stdio.h>
#ifndef PREFIX_STR
#define PREFIX_STR "prog2"
#endif
#define BSZ 1024
int main(){
    char buf[BSZ];
    while(fgets(buf, BSZ, stdin))
        printf("%s: %s", PREFIX_STR, buf);
    if(ferror(stdin)) { perror("fgets error"); return 1; }
}
