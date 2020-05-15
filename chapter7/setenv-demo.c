// setenv-demo.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char s[] = "abc";
    char* v = NULL;
    if(setenv("X", s, 1)==-1){
        perror("setenv error"); return 1;
    }
    strncpy(s, "def", sizeof(s));
    if((v=getenv("X"))==NULL){
        fputs("No variant in environment\n", stdout);
    }else{
        printf("s = %p, v = %p\n", s, v);
        printf("X=%s\n", v);
    }
}

