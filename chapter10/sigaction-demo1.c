// sigaction-demo1.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_deal(int signo){
    switch (signo)
    {
    case SIGQUIT: printf("received SIGQUIT\n"); break;
    case SIGTSTP: printf("received SIGTSTP\n"); break;
    case SIGINT: printf("received SIGINT\n"); break;
    default: printf("received %d\n", signo);
    }
    sleep(10);
    printf("exit sig_deal\n");
}
void show_sigaction(const char* prefix, struct sigaction* action){
    printf("%s:\n", prefix);
    if(action->sa_handler == SIG_IGN){
        printf("\tsa_handler: SIG_IGN\n");
    }else if (action->sa_handler == SIG_DFL){
        printf("\tsa_handler: SIG_DFL\n");
    }else{
        // 在 sa_handler 为用户自定义时, sa_mask 才有效
        // 表示在执行信号处理函数期间需要屏蔽的信号集
        printf("\tsa_hander: %p\n\tsa_maks: ", action->sa_handler);
        if(sigismember(&(action->sa_mask), SIGQUIT)){
            printf(" SIGQUIT ");    /* 信号处理期间屏蔽Ctrl+\ */
        }else if(sigismember(&(action->sa_mask), SIGTSTP)){
            printf(" SIGTSTP ");    /* 信号处理期间屏蔽Ctrl+Z */
        }else if(sigismember(&(action->sa_mask), SIGINT)){
            printf(" SIGINT ");  /* 信号处理期间屏蔽Ctrl+C */
        }
        printf("\n");
    }
}

int main(){
    struct sigaction action;
    sigset_t sigmask;
    sigaction(SIGQUIT, NULL, &action);
    printf("sig_deal address: %p\n", sig_deal);
    show_sigaction("0 action", &action);
    action.sa_handler = sig_deal;
    sigemptyset(&sigmask);
    // 信号处理函数执行期间屏蔽 SIGTSTP
    sigaddset(&(action.sa_mask), SIGTSTP);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGQUIT,  NULL, &action);
    show_sigaction("1 action", &action);
    signal(SIGTSTP, sig_deal);
    signal(SIGINT, sig_deal);
    for( ; ;) pause();
}

