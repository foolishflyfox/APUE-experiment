// 15-34-POSIX.c
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void opts(){
    const char *semname = "helloworld";
    sem_t *semp = sem_open(semname, O_CREAT, 0666, 1);
    if(SEM_FAILED==semp) { perror("sem_open error"); exit(1); }
    for(int i=0; i<1000000; ++i){
        if(sem_wait(semp)==-1) { perror("sem_wait error"); return; }
        if(sem_post(semp)==-1) { perror("sem_post error"); return; }
    }
}
int main(){
    pid_t pid1, pid2;
    if((pid1=fork())==-1){ perror("fork 1 error"); exit(1); }
    if(pid1==0) { opts(); exit(0); }
    if((pid2=fork())==-1){ perror("fork 2 error"); exit(1); }
    if(pid2==0) { opts(); exit(0); }
    opts();
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

