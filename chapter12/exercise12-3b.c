// exercise12-3b.c
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

const char* nms[] = {"sub thread", "main thread"};
pthread_t g_pid;
void foo(){
    sigset_t nsigs, osigs;
    sigfillset(&nsigs);
    if(pthread_sigmask(SIG_BLOCK, &nsigs, &osigs)){
        fprintf(stderr, "first foo sigprocmask error"); return;
    }
    printf("%s: begin foo\n", nms[pthread_equal(g_pid, pthread_self())]);
    sleep(3);
    printf("%s: end foo\n", nms[pthread_equal(g_pid, pthread_self())]);
    if(sigprocmask(SIG_SETMASK, &osigs, NULL)==-1){
        perror("second foo sigprocmask error"); return;
    }
}
void sig_alrm(int signo){
    foo();
}
void* thr_fn(void* arg){
    foo();
    return NULL;
}

int main(){
    if(signal(SIGALRM, sig_alrm)==SIG_ERR){
        perror("signal(SIGALRM) error"); return 1;
    }
    g_pid = pthread_self();
    pthread_t tid;
    if(pthread_create(&tid, NULL, thr_fn, NULL)){
        fprintf(stderr, "create thread error\n"); return 1;
    }
    alarm(1);
    void* tret;
    if(pthread_join(tid, &tret))
        fprintf(stderr, "join thread error\n");
}
