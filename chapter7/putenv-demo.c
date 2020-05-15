// putenv-demo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char s[] = "X=abc";
    char* v = NULL;
    if(putenv(s)==-1){
        perror("putenv error"); return 1;
    }
    strncpy(s, "X=def", sizeof(s));
    if((v=getenv("X"))==NULL){
        fputs("No variant in environment\n", stdout);
    }else{
        printf("s = %p, v = %p\n", s, v);
        printf("X=%s\n", v);
    }
}
