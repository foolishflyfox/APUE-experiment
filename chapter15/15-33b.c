// 15-33.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NLOOPS      1000
#define SIZE        sizeof(long)    /* size of shared memory area */

static int update(long *ptr){
    return ((*ptr)++);      /* return value before increment */
}

sigset_t old_mask;
static void sig_usr1(int signo){ }
static void TELL_WAIT(){
    sigset_t newmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    if(sigprocmask(SIG_BLOCK, &newmask, &old_mask) < 0) {
        perror("SIG_BLOCK error"); exit(1);
    }
    signal(SIGUSR1, sig_usr1);
}
void WAIT_CHILD(){ sigsuspend(&old_mask); }
void TELL_CHILD(pid_t pid){ kill(pid, SIGUSR1); }
void WAIT_PARENT(){ sigsuspend(&old_mask); }
void TELL_PARENT(pid_t pid){ kill(pid, SIGUSR1); }

int main(){
    int i, counter;
    pid_t pid;
    void *area;
    if((area = mmap(0, SIZE, PROT_READ|PROT_WRITE, 
                MAP_ANONYMOUS|MAP_SHARED, -1, 0))==MAP_FAILED){
        perror("mmap error"); exit(1);
    }
    TELL_WAIT();
    if((pid = fork()) < 0){
        perror("fork error"); exit(1);
    } else if(pid > 0){  /* parent */
        for(i=0; i<NLOOPS; i+=2){
            if((counter = update((long*)area))!=i){
                fprintf(stderr, "parent: expected %d, got %d\n", i, counter);
                exit(1);
            }
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    }else{
        for(i = 1; i < NLOOPS+1; i+=2){
            WAIT_PARENT();
            if((counter = update((long*)area))!=i){
                fprintf(stderr, "child: expected %d, got %d\n", i, counter);
                return 1;
            }
            TELL_PARENT(getppid());
        }
    }
    printf("i=%d\n", i);
    exit(0);
}
