// abort-demo.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sig_deal(int signo){
    if(signo==SIGABRT) printf("received SIGABRT\n");
    else if(signo==SIGUSR1) printf("received SIGUSR1\n");
    else printf("received %d\n", signo);
}

int main(){
    if(SIG_ERR==(signal(SIGABRT, sig_deal))){
        perror("signal error"); return 1;
    }
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGABRT);
    sigaddset(&newset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &newset, NULL);
    sleep(30);
    abort();
    printf("end of main\n");
}
