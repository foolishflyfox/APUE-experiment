// signal-fork.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void deal_signal(int signo){
    printf("%d received %d\n", getpid(), signo);
}

int main(){
    if(SIG_ERR == signal(SIGUSR1, deal_signal)){
        perror("signal error"); return 1;
    }
    pid_t pid;
    if(-1==(pid=fork())){
        perror("fork error"); return 1;
    }else if(pid==0){
        printf("child pid = %d\n", getpid());
        sleep(100); 
    }else{
        printf("parent pid = %d\n", getpid());
        sleep(100);
    }
}
