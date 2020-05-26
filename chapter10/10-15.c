// 10-15.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void sig_quit(int signo){
    printf("caught SIGQUIT\n");
    if(signal(SIGQUIT, SIG_DFL)==SIG_ERR){
        perror("can't reset SIGQUIT");
        _exit(1);
    }
}

int main(void){
    sigset_t newmask, oldmask, pendmask;
    if(SIG_ERR == signal(SIGQUIT, sig_quit)){
        perror("can't catch SIGQUIT"); return 1;
    }
    /* 阻塞 SIGQUIT，保存当前信号掩码 */
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0){
        perror("SIG_BLOCK error"); return 1;
    }
    sleep(5);  // SIGQUIT 在这5秒内都被阻塞
    if(sigpending(&pendmask) < 0){
        perror("sigpending error"); return 1;
    }
    if(sigismember(&pendmask, SIGQUIT))
        printf("\nSIGQUIT pending\n");
    /* 取消对 SIGQUIT 的阻塞 */
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0){
        perror("SIG_SETMASK error"); return 1;
    }
    printf("SIGQUIT unblocked\n");
    sleep(5);
}
