// mng-pgrp.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

void show_ids(){
    printf("pid = %d, ppid = %d, pgid = %d\n", 
            getpid(), getppid(), getpgrp());
}
void show_exit(){
    printf("%d exit\n", getpid());
}
void dealsig(int sig){
    printf("%ld: %d receive sig %d\n", time(NULL), getpid(), sig);
}

int main(){
    // 创建2个子进程
    pid_t p1, p2;
    show_ids();
    sigset(SIGINT, dealsig);
    for(int i=0; i<2; ++i){
        if(-1==(p1=fork())){
            perror("fork error"); _exit(1);
        }else if(p1==0){
            show_ids();
            // 子进程再创建两个子进程
            for(int j=0; j<2; ++j){
                if(-1==(p2=fork())){
                    perror("fork error"); _exit(1);
                }else if(p2==0){
                    show_ids();
                    sleep(100);
                    show_exit();
                    _exit(0);
                }
            }
            while(wait(NULL)!=-1);
            show_exit();
            _exit(0);
        }
    }
    sleep(2);
    killpg(getpgrp(), SIGINT);
    while(-1!=wait(NULL));
    show_exit();
}

