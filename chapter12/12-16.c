// 12-16.c
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

int         quitflag;   /* 通过线程设置为非零 */
sigset_t    mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void* thr_fn(void *arg){
    int signo;
    for( ; ;) {
        if(sigwait(&mask, &signo)){
            fprintf(stderr, "sigwait failed\n");
            pthread_exit(NULL);
        }
        switch (signo)
        {
        case SIGINT:
            printf("\ninterrupt\n"); break;
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag = 1;
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&waitloc);
            return 0;
        default:
            printf("unexpected signal %d\n", signo);
            exit(1);
        }
    }
}
int main() {
    int         err;
    sigset_t    oldmask;
    pthread_t   tid;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    if(pthread_sigmask(SIG_BLOCK, &mask, &oldmask)){
        fprintf(stderr, "pthread_sigmask error\n"); return 1;
    }
    if(pthread_create(&tid, NULL, thr_fn, NULL)){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    pthread_mutex_lock(&lock);
    while(quitflag == 0) pthread_cond_wait(&waitloc, &lock);
    pthread_mutex_unlock(&lock);
}
