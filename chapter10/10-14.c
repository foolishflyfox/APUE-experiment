// 10-14.c
#include <stdio.h>
#include <signal.h>
#include <errno.h>

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
int main(){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1); sigaddset(&sigset, SIGQUIT);
    if(-1==sigprocmask(SIG_BLOCK, &sigset, NULL)){
        perror("set sigprocmask error"); return 1;
    }
    pr_mask("current mask:");
}

