// 12-8.c
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

struct to_info{
    void* (*to_fn)(void*);       /* function */
    void *to_arg;               /* argument */
    struct timespec to_wait;    /* time to wait */
};

void * timeout_helper(void *arg){
    struct to_info *tip = arg;
    // 阻塞 to_wait.tv_sec 秒，to_wait.tv_nsec 纳秒
    nanosleep(&tip->to_wait, NULL);
    // 调用 to_fn 函数
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return NULL;
}
int makethread(void *(*fun)(void*), void* arg){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err!=0) return err;
    return pthread_create(&tid, &attr, fun, arg);
}
void timeout(const struct timespec *when, void* (*func)(void*), void *arg){
    struct timespec now;
    struct to_info *tip;
    int err;
    clock_gettime(CLOCK_REALTIME, &now);
    if ((when->tv_sec) > now.tv_sec ||
      (when->tv_sec==now.tv_sec && when->tv_nsec>now.tv_nsec)){
        // 没有达到指定时间 when
        tip = malloc(sizeof(struct to_info));
        if(tip!=NULL){
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if(when->tv_nsec >= now.tv_nsec){
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            }else{
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = 1000000000+when->tv_nsec-now.tv_nsec;
            }
            err = makethread(func, arg);
            if (err == 0) return;
            else free(&tip);
        }
    }
    /*
     * 执行下面的代码有3种情况：a、当前时间大于when, b、malloc失败, c、创建线程失败
     */
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void retry(void *arg){
    pthread_mutex_lock(&mutex);

    /* perform retry steps ... */

    pthread_mutex_unlock(&mutex);
}

int main(){
    int err, condition, arg;
    struct timespec when;

    if((err = pthread_mutexattr_init(&attr))!=0){
        fprintf(stderr, "pthread_mutexattr_init failed"); return 1;
    }
    if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)){
        fprintf(stderr, "can't set recursive type\n"); return 1;
    }
    /* continue processing ... */
    pthread_mutex_lock(&mutex);
    /*
     * Check the condition under the protection of a lock to
     * make the check and the call to timeout atomic.
     */
    if (condition){
        /* Calculate the absolute time when we want to retry. */
        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 10;      /* 10 seconds from now */
        CLOCK_REALTIME;
    }
    pthread_mutex_unlock(&mutex);

    /* continue processing ... */
    exit(0);
}


