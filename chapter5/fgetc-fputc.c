// fgetc-fputc.c
#include <stdio.h>

int main(){
    int c;
    while((c=fgetc(stdin))!=EOF){
        if(fputc(c, stdout)==EOF){
            perror("fputc error"); return 1;
        }
    }
    if(ferror(stdin)){
        perror("fgetc error"); return 1;
    }
}
