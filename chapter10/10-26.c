// 10-26.c
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
    if(cmdstring==NULL) return 1;
    if(-1==(pid=(fork())))return -1;
    else if(pid==0){
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127);
    }
    int status;
    if(-1==waitpid(pid, &status, 0)){
        if(errno!=EINTR) return -1;
    }
    return WEXITSTATUS(status);
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

