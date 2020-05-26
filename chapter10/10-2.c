// 10-2.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_user(int signo){
    if(signo==SIGUSR1) printf("received SIGUSR1\n");
    else if(signo==SIGUSR2) printf("received SIGUSR2\n");
    else fprintf(stderr, "received signal %d\n", signo);
}

int main(){
    if(signal(SIGUSR1, sig_user)==SIG_ERR){
        perror("can't catch SIGUSER1"); return 1;
    }
    if(signal(SIGUSR2, sig_user)==SIG_ERR){
        perror("can't catch SIGUSER2"); return 1;
    }
    for(;;) pause();
}
