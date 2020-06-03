// 12-6b.c
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#ifdef WITHLOCK
#define LOCK(lockptr) pthread_mutex_lock((lockptr))
#define UNLOCK(lockptr) pthread_mutex_unlock((lockptr))
#else
#define LOCK(lockptr) 
#define UNLOCK(lockptr) 
#endif

#ifndef RECURSIVE_LOCK
#define MUTEX_TYPE PTHREAD_MUTEX_NORMAL
#else
#define MUTEX_TYPE PTHREAD_MUTEX_RECURSIVE
#endif

typedef struct{
    const char* msg;
    int callbyfunc1;
    pthread_mutex_t lock;
}A;
void* func2(void* argv){
    A* x = argv;
    usleep(10000); // 保证 func1 先运行
    LOCK(&x->lock);
    if(x->callbyfunc1==0) x->msg = "world";
    printf("%lu: func2, %s\n", time(NULL), x->msg);
    UNLOCK(&x->lock);
    return NULL;
}

void* func1(void* argv){
    A* x = argv;
    printf("%lu: func1 start\n", time(NULL));
    LOCK(&x->lock);
    x->callbyfunc1 = 1;
    x->msg = "from func1";

#ifdef TMP_RELEASE
    x->callbyfunc1 = 0; UNLOCK(&x->lock); func2(argv);
    LOCK(&x->lock); x->callbyfunc1 = 1;
#else
    func2(argv);
#endif

    sleep(1);

#ifdef TMP_RELEASE
    x->callbyfunc1 = 0; UNLOCK(&x->lock); func2(argv);
    LOCK(&x->lock); x->callbyfunc1 = 1;
#else
    func2(argv);
#endif

    x->callbyfunc1 = 0; UNLOCK(&x->lock);
    printf("%lu: func1 end\n", time(NULL));
    return NULL;
}
int main(){
    A x; x.msg = "init";
    pthread_t tid1, tid2;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, MUTEX_TYPE);
    pthread_mutex_init(&x.lock, &mutexattr);
    if(0!=pthread_create(&tid1, NULL, func1, &x)){
        fprintf(stderr, "error: run func1 in thread\n"); return 1;
    }
    if(0!=pthread_create(&tid2, NULL, func2, &x)){
        fprintf(stderr, "error: run func2 in thread\n"); return 1;
    }
    void* tret;
    if(0!=pthread_join(tid1, &tret)){
        fprintf(stderr, "error: join func1 error"); return 1;
    }
    if(0!=pthread_join(tid2, &tret)){
        fprintf(stderr, "error: join func2 error"); return 1;
    }
}

