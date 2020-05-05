// ungetc-demo.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "r");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    int c = 0;
    float v;
    while((c=getc(fp))!=EOF){
        if(c<'0' || c>'9') continue;
        else{
            ungetc(c, fp);
            fscanf(fp, "%f", &v);
            printf("%g  ", v);
        }
    }
    if(ferror(fp)){
        perror("getc error"); return 1;
    }
    putchar('\n');
}

