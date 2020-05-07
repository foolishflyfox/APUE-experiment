// exercise5-2.c
#include <stdio.h>

#define BUFFSIZE 4

int main(){
    char buf[BUFFSIZE];
    while(fgets(buf, BUFFSIZE, stdin)!=NULL){
        if(fputs(buf, stdout)==EOF){
            perror("fputs error"); return 1;
        }
    }
    if(ferror(stdin)){
        perror("fgets error"); return 1;
    }
}

