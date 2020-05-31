// pthread-sigproc.c
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void sig_alrm(int signo){
    printf("%ld: received SIGALRM\n", time(NULL));
}
void* foo(void* argv){
    sleep(2);
    printf("%ld: end of foo\n", time(NULL));
    return NULL;
}

int main(){
    if(SIG_ERR == signal(SIGALRM, sig_alrm)){
        perror("signal(SIGALRM) error");
        return 1;
    }
    alarm(1);
    printf("%ld: begin thread\n", time(NULL));
    pthread_t tid;
    int err = pthread_create(&tid, NULL, foo, NULL);
    if(err!=0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(err));
        return 1;
    }
    sleep(3);
    printf("%ld: end of main\n", time(NULL));
    void* tret;
    if((err = pthread_join(tid, &tret))!=0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(err));
        return 1;
    }
}

