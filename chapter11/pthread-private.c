// pthread-private.c
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
int global_value;
void* foo(void* argv){
    sigset_t t_set;
    sigemptyset(&t_set);
    sigaddset(&t_set, SIGALRM);
    sigprocmask(SIG_BLOCK, &t_set, NULL);
    global_value = 10;
    if(sigprocmask(SIG_BLOCK, &t_set, NULL)==-1){
        perror("sigprocmask error");
    }
    errno = 10;
    return NULL;
}
void sig_alrm(int signo){
    printf("received SIGALRM\n");
}

int main(){
    pthread_t tid;
    void* tret;
    global_value = 0;
    errno = 0;
    if(signal(SIGALRM, sig_alrm)==SIG_ERR){
        perror("signal error");
    }
    alarm(1);
    int err = pthread_create(&tid, NULL, foo, NULL);
    if(err!=0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(err));
        return 1;
    }
    err = pthread_join(tid, &tret);
    if(err!=0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(err));
        return 1;
    }
    printf("global_value is %s\n", global_value==10?"public":"private");
    printf("errno is %s\n", errno==10?"public":"private");
    sleep(3);
}
