// feof-ferror-demo.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "w");
    if(fgetc(fp)==EOF){
        if(ferror(fp)) perror("1 ferror");
        if(feof(fp)) perror("1 feof");
    }
    fclose(fp);
    fp = fopen("tmp", "r");
    if(fgetc(fp)==EOF){
        if(ferror(fp)) perror("2 ferror");
        if(feof(fp)) perror("2 feof");
    }
}

