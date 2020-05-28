// 10-29.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void sig_alarm(int signo){
    /* noting to do, just return to wake up the pause */
}

static unsigned int sleep3(unsigned int seconds){
    struct sigaction newact, oldact;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept;
    /* set our handler, save previous information */
    newact.sa_handler = sig_alarm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    /* block SIGALRM and save current signal mask */
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    alarm(seconds);
    suspmask = oldmask;

    /* make sure SIGALRM isn't blocked */
    sigdelset(&suspmask, SIGALRM);
    /* wait for any signal to be caught */
    sigsuspend(&suspmask);

    /* some signal has been caught, SIGALRM is now blocked */

    unslept = alarm(0);
    /* reset previous action */
    sigaction(SIGALRM, &oldact, NULL);
    /* reset signal mask, which unblocks SIGALRM */
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;

    if(signal(SIGALRM, sig_alarm)==SIG_ERR)
        return(seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}

int main(){
    printf("t0: %ld\n", time(NULL));
    sleep3(5);
    printf("t1: %ld\n", time(NULL));
}

