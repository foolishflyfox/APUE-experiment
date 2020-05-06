// fread-array.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "r");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    float buf[4];
    if(fread(buf, sizeof(float), 4, fp)<4){
        perror("fread error"); return 1;
    }else{
        for(int i=0; i<4; ++i) printf("%f  ", buf[i]);
        putchar('\n');
    }
}
