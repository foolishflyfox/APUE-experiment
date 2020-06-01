// barrier-demo2.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int remain;
    pthread_rwlock_t rwlock;
}my_barrier_t;

void* lock_rwlock(void* argv){
    pthread_rwlock_t* rwlock = (pthread_rwlock_t*)argv;
    pthread_rwlock_wrlock(rwlock);
    return NULL;
}

void my_barrier_init(my_barrier_t* barrier, int threads){
    barrier->remain = threads;
    pthread_rwlock_init(&barrier->rwlock, NULL);
    // pthread_rwlock_wrlock(&barrier->rwlock);
    // 开辟新线程进行加锁，否则主线程等待时会出现死锁错误
    pthread_t tid;
    pthread_create(&tid, NULL, lock_rwlock, &barrier->rwlock);
    void* tret;
    pthread_join(tid, &tret);
}
int my_barrier_wait(my_barrier_t* barrier){
    barrier->remain -= 1;
    if(barrier->remain <= 0){
        pthread_rwlock_unlock(&barrier->rwlock);
        return -1;
    }else{
        pthread_rwlock_rdlock(&barrier->rwlock);
        return 0;
    }
}

my_barrier_t b;

void* foo(void* argv){
    long ss = (long)argv;
    pthread_t tid = pthread_self();
    printf("%lu: %lu start, sleep %lds\n", 
            (unsigned long)tid, time(NULL), ss);
    sleep(ss);
    int ret = my_barrier_wait(&b);
    printf("%lu: %lu end, sleep %lds, return %d\n", 
            (unsigned long)tid, time(NULL), ss, ret);
    return NULL;
}

int main(){
    pthread_t tids[3];
    long ss[3] = {2,5,3};
    pthread_t tid = pthread_self();
    printf("main tid = %lu\n", (unsigned long)tid);
    int threads = 3, err;
    my_barrier_init(&b, threads+1);
    for(int i=0; i<threads; ++i){
        err = pthread_create(tids+i, NULL, foo, (void*)ss[i]);
        if(err!=0){
            fprintf(stderr, "can't create thread\n");
            return 1;
        }
    }
    int ret = my_barrier_wait(&b);
    printf("%lu: %lu end, return %d\n", (unsigned long)tid, time(NULL), ret);
    for(int i=0; i<3; ++i){
        void* tret;
        pthread_join(tids[i], &tret);
    }
}

