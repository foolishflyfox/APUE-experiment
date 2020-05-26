// 10-8.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <setjmp.h>
typedef void Sigfunc(int);
static jmp_buf env_alrm;
static void deal_signal(int signo){
    printf("%ld: received signal %d\n", time(NULL), signo);
}

static void sig_alarm(int signo){
    longjmp(env_alrm, 1);
}

static unsigned int sleep2(unsigned int seconds){
    Sigfunc* action = signal(SIGALRM, sig_alarm);
    if(action == SIG_ERR)
        return(seconds);
    volatile int origin_t;
    if(setjmp(env_alrm)==0){
        origin_t = alarm(seconds);
        sleep(2*seconds);
        pause();
    }
    signal(SIGALRM, action);
    if(origin_t > seconds) return alarm(origin_t-seconds);
    return (alarm(0));
}

int main(){
    if(SIG_ERR == (signal(SIGALRM, deal_signal))){
        perror("signal error"); return 1;
    }
    alarm(5);
    printf("t0: %ld\n", time(NULL));
    sleep2(3);
    printf("t1: %ld\n", time(NULL));
    pause();
}

