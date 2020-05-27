// 10-24.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) { sigflag = 1; }

void TELL_WAIT(){
    if(signal(SIGUSR1, sig_usr) == SIG_ERR){
        perror("signal(SIGUSR1) error"); _exit(1);
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR){
        perror("signal(SIGUSR2) error"); _exit(1);
    }
    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        perror("SIG_BLOCK error"); _exit(1);
    }
}
void WAIT_PARENT(){
    while(sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); _exit(1);
    }
}
void WAIT_CHILD(){
    while(sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); _exit(1);
    }
}
void TELL_PARENT(pid_t pid){
    kill(pid, SIGUSR2);
}
void TELL_CHILD(pid_t pid){
    kill(pid, SIGUSR1);
}
static void charatatime(char *str){
    char* ptr;
    int c;
    setbuf(stdout, NULL);  /* 设置标准输出为无缓冲模式 */
    for(ptr = str; (c=*ptr)!=0; ++ptr)
        putc(c, stdout);
}

int main(){
    pid_t pid;
    TELL_WAIT();
    if((pid=fork())<0){
        perror("fork error");
    }else if(pid==0){
        WAIT_PARENT();
        charatatime("output from child\n");
        TELL_PARENT(getppid());
    }else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
    return 0;
}

