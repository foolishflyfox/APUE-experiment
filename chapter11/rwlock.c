// rwlock.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
pthread_rwlock_t lock;

void* foo(void* argv){
    printf("%ld: start\n", time(NULL));
    pthread_rwlock_rdlock(&lock);
    printf("%ld: end\n", time(NULL));
    return NULL;
}
void* unlock_rwlock(void* argv){
    pthread_rwlock_t* rwlock = (pthread_rwlock_t*)argv;
    pthread_rwlock_unlock(rwlock);
    return NULL;
}

void* lock_rwlock(void* argv){
    // pthread_rwlock_t* rwlock = (pthread_rwlock_t*)argv;
    pthread_rwlock_wrlock(&lock);
    return NULL;
}

int main(){
    pthread_t tids[4];
    pthread_t tid;
    pthread_rwlock_init(&lock, NULL);
    pthread_rwlock_wrlock(&lock);
    // 下面的语句导致解锁后其他线程不能解除阻塞
    // pthread_create(&tid, NULL, lock_rwlock, &lock);
    void* tret;
    usleep(100);
    // pthread_join(tid, &tret);
    for(int i=1; i<4; ++i){
        pthread_create(tids+i, NULL, foo, NULL);
    }
    sleep(3);
    int err = 0;
    err = pthread_create(tids, NULL, unlock_rwlock, &lock);
    if(err!=0){
        fprintf(stderr, "pthread_create error\n");
    }
    pthread_rwlock_unlock(&lock);
    pthread_rwlock_unlock(&lock);
    for(int i=0; i<4; ++i){
        void* tret;
        pthread_join(tids[i], &tret);
    }
}
