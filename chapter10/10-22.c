// 10-22.c
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
static void sig_int(int signo){
    pr_mask("\nin sig_int: ");
}

int main(){
    sigset_t newmask, oldmask, waitmask;
    pr_mask("program start: ");
    if(signal(SIGINT, sig_int)==SIG_ERR){
        perror("signal(SIGINT) error"); return 1;
    }
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);
    /* 阻塞 SIGINT */
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask)<0){
        perror("SIG_BLOCK error"); return 1;
    }
    /* 代码临界区 */
    pr_mask("in critical region: ");
    /* 暂停，允许除了 SIGUSR1 以外的所有信号 */
    if(sigsuspend(&waitmask) != -1){
        perror("sigsuspend error"); return 1;
    }
    pr_mask("after return from sigsuspend: ");
    /* 恢复原信号配置，不再阻塞 SIGINT */
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); return 1;
    }
    // 继续其他操作
    pr_mask("program exit: ");
}
