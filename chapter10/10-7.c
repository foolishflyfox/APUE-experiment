// 10-7.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void sig_alarm(int signo){
    /* noting to do, just return to wake up the pause */
}

static unsigned int sleep1(unsigned int seconds){
    if(signal(SIGALRM, sig_alarm)==SIG_ERR)
        return(seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}

int main(){
    printf("t0: %ld\n", time(NULL));
    sleep1(5);
    printf("t1: %ld\n", time(NULL));
}

