// 15-19.c
#include <stdio.h>
#define MAXLINE 1024

int main(){
    int int1, int2;
    char line[MAXLINE];
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
