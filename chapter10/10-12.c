// 10-12.c
#include <signal.h>
#include <errno.h>

// NSIG 定义在 <signal.h>，比允许的最大信号值大1
#define SIGBAD(signo) ((signo)<=0 || (signo)>=NSIG)

int sigaddset(sigset_t* set, int signo){
    if(SIGBAD(signo)) { errno = EINVAL; return -1; }
    *set |= (1<<(signo-1));
    return 0;
}
int sigdelset(sigset_t* set, int signo){
    if(SIGBAD(signo)) {errno = EINVAL; return -1;}
    *set &= ~(1<<(signo-1));
    return 0;
}
int sigismember(const sigset_t* set, int signo){
    if(BADSIG(signo)) {errno = EINVAL; return -1;}
    return (*set & (1<<(signo-1)))?1:0;
}

