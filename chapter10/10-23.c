// 10-23.c
#include <stdio.h>
#include <signal.h>

volatile sig_atomic_t quitflag;   /* 由信号处理程序设置为非0 */

static void sig_int(int signo){
    if(signo == SIGINT) printf("\ninterrupt\n");
    else if(signo == SIGQUIT) quitflag = 1;
}
int main(){
    sigset_t newmask, oldmask, zeromask;
    if(signal(SIGINT, sig_int) == SIG_ERR){
        perror("signal(SIGINT) error"); return 1;
    }
    if(signal(SIGQUIT, sig_int) == SIG_ERR){
        perror("signal(SIGQUIT) error"); return 1;
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    /* 阻塞 SIGQUIT 信号 */
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        perror("SIG_BLOCK error"); return 1;
    }
    while(quitflag == 0) {
        sigsuspend(&zeromask);
        printf("after sigsuspend\n");
    }
    printf("out of while\n");
    quitflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); return 1;
    }
}
