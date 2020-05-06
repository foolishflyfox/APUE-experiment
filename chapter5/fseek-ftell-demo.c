// fseek-ftell-demo.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "r+");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    int pos;
    if(fseek(fp, -2, SEEK_END)==-1){
        perror("fseek error"); return 1;
    }
    if((pos=ftell(fp))==-1){
        perror("ftell error"); return 1;
    }else {
        printf("current pos: %d\n", pos);
    }
}
