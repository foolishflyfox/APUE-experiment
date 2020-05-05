// fopen-demo.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "r+");
    char c;
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    if(fprintf(fp, "abc")<0)
        perror("first fpritnf error");
    fread(&c, 1, 1, fp);
    printf("get '%c'\n", c);
    if(fprintf(fp, "def")<0)
        perror("second fprintf error");
}
