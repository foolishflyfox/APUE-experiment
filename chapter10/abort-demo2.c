// abort-demo2.c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_abrt(int signo){
    printf("received SIGABRT\n");
    exit(0);
}
int main(){
    if(SIG_ERR==signal(SIGABRT, sig_abrt)){
        perror("signal(SIGABRT) error");
    }
    sleep(1);
    abort();
    printf("end of main\n");
}
