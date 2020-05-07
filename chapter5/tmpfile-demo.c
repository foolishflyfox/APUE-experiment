// tmpfile-demo.c
#include <stdio.h>
#include <unistd.h>

int main(){
    FILE* fp;
    if((fp=tmpfile())==NULL){
        perror("tmpfile error"); return 1;
    }
    fputs("one line of output\n", fp);
    char line[64];
    rewind(fp);
    if(fgets(line, 64, fp)==NULL){
        perror("fgets error"); return 1;
    }
    fputs(line, stdout);
}
