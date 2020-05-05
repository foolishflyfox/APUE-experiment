// fgets-demo.c
#include <stdio.h>
#include <string.h>

int main(){
    char buf[5];
    FILE* fp = fopen("tmp", "r");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    while(fgets(buf, 5, fp)!=NULL){
        printf("read %lu char: %s\n", strlen(buf), buf);
    }
    if(ferror(fp)){
        perror("fgets error");
        return 1;
    }
}
