// 15-15.c
#include <stdio.h>
#include <sys/wait.h>
#define MAXLINE 1024
int main(){
    char line[MAXLINE];
    FILE *fpin;
    if((fpin = popen("./myuclc", "r")) == NULL){
        perror("popen error"); return 1;
    }
    for( ; ; ){
        fputs("prompt> ", stdout);
        fflush(stdout);
        if(fgets(line, MAXLINE, fpin) == NULL) /* read from pipe */
            break;
        if(fputs(line, stdout) == EOF){
            perror("fputs error to pipe");
        }
    }
    if(pclose(fpin) == -1) { perror("pclose error"); return 1; }
    putchar('\n');
    return 0;
}
