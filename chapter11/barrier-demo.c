// barrier-demo.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_barrier_t b;

void* foo(void* argv){
    long ss = (long)argv;
    pthread_t tid = pthread_self();
    printf("%lu: %lu start, sleep %lds\n", 
            (unsigned long)tid, time(NULL), ss);
    sleep(ss);
    int ret = pthread_barrier_wait(&b);
    printf("%lu: %lu end, sleep %lds, return %d\n", 
            (unsigned long)tid, time(NULL), ss, ret);
    return NULL;
}

int main(){
    pthread_t tids[3];
    long ss[3] = {2,5,3};
    pthread_t tid = pthread_self();
    printf("PTHREAD_BARRIER_SERIAL_THREAD = %d\n", PTHREAD_BARRIER_SERIAL_THREAD);
    printf("main tid = %lu\n", (unsigned long)tid);
    int threads = 3, err;
    pthread_barrier_init(&b, NULL, threads+1);
    for(int i=0; i<threads; ++i){
        err = pthread_create(tids+i, NULL, foo, (void*)ss[i]);
        if(err!=0){
            fprintf(stderr, "can't create thread\n");
            return 1;
        }
    }
    int ret = pthread_barrier_wait(&b);
    printf("%lu: %lu end, return %d\n", (unsigned long)tid, time(NULL), ret);
    for(int i=0; i<3; ++i){
        void* tret;
        pthread_join(tids[i], &tret);
    }
}

