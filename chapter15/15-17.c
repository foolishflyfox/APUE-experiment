// 15-17.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 1023
int main(){
    int n, int1, int2;
    char line[MAXLINE+1];
    while((n = read(STDIN_FILENO, line, MAXLINE)) > 0){
        line[n] = 0;
        if(sscanf(line, "%d%d", &int1, &int2) == 2){
            sprintf(line, "%d\n", int1+int2);
            n = strlen(line);
            if(write(STDOUT_FILENO, line, n)!=n){
                perror("write error"); return 1;
            }
        }else{
            if(write(STDOUT_FILENO, "invalid args\n", 13)!=13){
                perror("write error"); return 1;
            }
        }
    }
    return 0;
}
