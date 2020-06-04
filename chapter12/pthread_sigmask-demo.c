// pthread_sigmask-demo.c
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

sigset_t g_sigset;
void sig_alrm(int signo) {
    printf("%lu: received SIGALRM\n", (unsigned long)pthread_self());
}
void* foo(void* arg){
    printf("%lu: enter foo\n", (unsigned long)pthread_self());
#ifdef BLOCK_FOO
    if(pthread_sigmask(SIG_BLOCK, &g_sigset, NULL))
        fprintf(stderr, "foo pthread_sigmask error\n");
#endif
    sleep(3);
    return NULL;
}
void* bar(void* arg){
    printf("%lu: enter bar\n", (unsigned long)pthread_self());
#ifdef BLOCK_BAR
    if(pthread_sigmask(SIG_BLOCK, &g_sigset, NULL))
        fprintf(stderr, "bar pthread_sigmask error\n");
#endif
    sleep(3);
    return NULL;
}

int main(){
    sigemptyset(&g_sigset);
    sigaddset(&g_sigset, SIGALRM);
    if(SIG_ERR==signal(SIGALRM, sig_alrm)){
        fprintf(stderr, "signal(SIGALRM) error\n"); return 1;
    }
    printf("%lu: main thread\n", (unsigned long)pthread_self());
    alarm(1);
    pthread_t tids[2];
    if(pthread_create(&tids[0], NULL, foo, NULL))
        fprintf(stderr, "can't run foo in thread\n");
    if(pthread_create(&tids[1], NULL, bar, NULL))
        fprintf(stderr, "can't run bar in thread\n");
#ifdef BLOCK_MAIN
    if(pthread_sigmask(SIG_BLOCK, &g_sigset, NULL))
        fprintf(stderr, "main pthread_sigmask error");
#endif
    void* tid;
    for(int i=0; i<2; ++i){
        if(pthread_join(tids[i], &tid))
            fprintf(stderr, "join thread %d error\n", i);
    }
}


