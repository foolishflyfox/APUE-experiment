// 10-7b.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void deal_signal(int signo){
    printf("%ld: received signal %d\n", time(NULL), signo);
}

static void sig_alarm(int signo){
    /* noting to do, just return to wake up the pause */
}

static unsigned int sleep1(unsigned int seconds){
    if(signal(SIGALRM, sig_alarm)==SIG_ERR)
        return(seconds);
    int origin_t = alarm(seconds);
    pause();
    if(origin_t > seconds) return alarm(origin_t-seconds);
    return (alarm(0));
}

int main(){
    if(SIG_ERR == (signal(SIGALRM, deal_signal))){
        perror("signal error"); return 1;
    }
    alarm(5);
    printf("t0: %ld\n", time(NULL));
    sleep1(3);
    printf("t1: %ld\n", time(NULL));
    pause();
}

