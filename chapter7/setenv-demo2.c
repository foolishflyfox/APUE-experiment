// setenv-demo2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setLANG(const char* value){
    if(setenv("LANG", value, 1)==-1){
        perror("setenv error"); return;
    }
    char* p = getenv("LANG");
    printf("LANG = %-12s p = %p\n", p, p);
}

int main(){
    const char* p = getenv("LANG");
    printf("LANG = %-12s p = %p\n", p, p);
    setLANG("xxx");
    setLANG("yyyyy");
    setLANG("xxx");
    setLANG("xyz");
}
