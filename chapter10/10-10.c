// 10-10.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MAXLINE 1024
static void sig_alrm(int signo){
    /* nothing to do, just return to interrupte the read */
}

int main(void){
    int n;
    char line[MAXLINE];
    if(SIG_ERR==(signal(SIGALRM, sig_alrm))){
        perror("signal(SIGALRM) error"); return 1;
    }
    alarm(10);
    if((n=read(STDIN_FILENO, line, MAXLINE)) < 0){
        perror("read error"); return 1;
    }
    alarm(0);
    write(STDOUT_FILENO, line, n);
}
