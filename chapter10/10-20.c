// 10-20.c
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t canjump;
static sigjmp_buf jmpbuf;

void pr_mask(const char* str){
    sigset_t sigset;
    int errno_save = errno;
    if(sigprocmask(0, NULL, &sigset)<0){
        perror("get sigprocmask error"); return;
    }else{
        printf("%s", str);
        if(sigismember(&sigset, SIGINT)) printf(" SIGINT");
        if(sigismember(&sigset, SIGQUIT)) printf(" SIGQUIT");
        if(sigismember(&sigset, SIGUSR1)) printf(" SIGUSR1");
        if(sigismember(&sigset, SIGALRM)) printf(" SIGALRM");
        /* 可添加新的信号显示 */
        fputc('\n', stdout);
    }
    errno = errno_save;
}
static void sig_usr1(int signo){
    time_t starttime;
    if(canjump == 0) return;
    pr_mask("start sig_usr1: ");
    alarm(3);
    starttime = time(NULL);
    for( ; ; )
        if(time(NULL) > starttime + 5) break;
    pr_mask("finishing sig_usr1: ");
    canjump = 0;
    siglongjmp(jmpbuf, 1);
}
static void sig_alrm(int signo){
    pr_mask("in sig_alrm: ");
}

int main(){
    if(signal(SIGUSR1, sig_usr1) == SIG_ERR){
        perror("signal(SIGUSR1) error"); return 1;
    }
    if(signal(SIGALRM, sig_alrm) == SIG_ERR){
        perror("signal(SIGALRM) error"); return 1;
    }
    pr_mask("starting main: ");
    if(sigsetjmp(jmpbuf, 1)) {
        pr_mask("ending main: ");
        exit(0);
    }
    canjump = 1;
    for(;;) pause();
}
