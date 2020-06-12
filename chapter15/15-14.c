// 15-14.c
#include <stdio.h>
#include <ctype.h>
int main(){
    int c;
    while((c = getchar()) != EOF){
        if(isupper(c)) c = tolower(c);
        if(putchar(c) == EOF) { perror("output error"); return 1; }
        if(c == '\n') fflush(stdout);
    }
    return 0;
}

