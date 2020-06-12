// 15-19b.c
#include <stdio.h>
#define MAXLINE 1024

int main(){
    int int1, int2;
    char line[MAXLINE];
    if(setvbuf(stdin, NULL, _IOLBF, 0)!=0){
        perror("setvbuf error"); return 1;
    }
    if(setvbuf(stdout, NULL, _IOLBF, 0)!=0){
        perror("setvbuf error"); return 1;
    }
    while(fgets(line, MAXLINE, stdin) != NULL){
        if(sscanf(line, "%d%d", &int1, &int2) == 2){
            if(printf("%d\n", int1+int2)==EOF){
                perror("printf error"); return 1;
            }
        }else{
            if(printf("invalid args\n")==EOF){
                perror("printf error"); return 1;
            }
        }
    }
    return 0;
}
