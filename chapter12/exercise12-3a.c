// exercise12-3a.c
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

const char* rolenames[] = {"child", "parent"};
int role = 1;
void foo(){
    sigset_t nsigs, osigs;
    sigfillset(&nsigs);
    if(sigprocmask(SIG_BLOCK, &nsigs, &osigs)==-1){
        perror("first foo sigprocmask error"); return;
    }
    printf("%s: begin foo\n", rolenames[role]);
    sleep(3);
    printf("%s: end foo\n", rolenames[role]);
    if(sigprocmask(SIG_SETMASK, &osigs, NULL)==-1){
        perror("second foo sigprocmask error"); return;
    }
}
void sig_alrm(int signo){
    foo();
}

int main(){
    if(signal(SIGALRM, sig_alrm)==SIG_ERR){
        perror("signal(SIGALRM) error"); return 1;
    }
    pid_t pid = fork();
    if(pid==-1){
        perror("fork error"); return 1;
    }
    alarm(1);
    if(pid==0){
        role = 0;
        foo();
    }else{
        int stat;
        if(waitpid(pid, &stat, 0)==-1) perror("wait pid error");
    }
}
