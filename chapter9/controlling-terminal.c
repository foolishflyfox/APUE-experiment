// controlling-terminal.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef void(*sighandler_t)(int);
sighandler_t sigset(int sig, sighandler_t disp);

void deal_signal(int sig){
    printf("pid %d receive signal %d\n", getpid(), sig);
}

int main(){
    int pid;
    printf("parent pid = %d\n", getpid());
    sigset(SIGINT, deal_signal);
    sigset(SIGQUIT, deal_signal);
    for(int i=0; i<3; ++i){
        if(-1==(pid=fork())){
            perror("fork error"); return 1;
        }else if(pid==0){
            sleep(1000);
            _exit(0);
        }
    }
    while(-1!=wait(NULL));
}

