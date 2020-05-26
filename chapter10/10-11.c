// 10-11.c
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

#define MAXLINE 1024
static jmp_buf env_alrm;
static void sig_alrm(int signo){
    longjmp(env_alrm, 1);
}

int main(){
    int n;
    char line[MAXLINE];
    if(SIG_ERR==(signal(SIGALRM, sig_alrm))){
        perror("signal(SIGALRM) error"); return 1;
    }
    if(setjmp(env_alrm)!=0){
        fprintf(stderr, "read timeout\n"); return 1;
    }
    alarm(10);
    if((n=read(STDIN_FILENO, line, MAXLINE)) < 0){
        perror("read error"); return 1;
    }
    alarm(0);
    write(STDOUT_FILENO, line, n);
}
