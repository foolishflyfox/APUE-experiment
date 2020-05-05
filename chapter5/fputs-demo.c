// fputs-demo.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "w");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    fputs("abc", fp); puts("abc");
    fputs("def\n", fp); puts("def\n");
}
