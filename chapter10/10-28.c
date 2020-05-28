// 10-28.c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
static void sig_int(int signo){
    printf("caught SIGINT\n");
}
static void sig_chld(int signo){
    printf("caught SIGCHLD\n");
}
static int mysystem(const char* cmdstring){
    pid_t pid;
    int status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t chldmask, savemask;
    if(cmdstring==NULL) return 1;
    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if(sigaction(SIGINT, &ignore, &saveintr) < 0) return -1;
    if(sigaction(SIGQUIT, &ignore, &savequit) < 0) return -1;
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if(sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0) return -1;

    if(-1==(pid=(fork()))) status = -1;
    else if(pid==0){
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127);
    }else{
        while(waitpid(pid, &status, 0) < 0)
            if(errno != EINTR){
                status = -1;
                break;
            }
    }
    if(sigaction(SIGINT, &saveintr, NULL) < 0) return -1;
    if(sigaction(SIGQUIT, &savequit, NULL) < 0) return -1;
    if(sigprocmask(SIG_SETMASK, &savemask, NULL) < 0) return -1;
    return status;
}
int main(void){
    if(signal(SIGINT, sig_int)==SIG_ERR){
        perror("signal(SIGINT) error"); return 1;
    }
    if(signal(SIGCHLD, sig_chld) == SIG_ERR){
        perror("signal(SIGCHLD) error"); return 1;
    }
    if(mysystem("/bin/ed") < 0){
        perror("system() error"); return 1;
    }
}

