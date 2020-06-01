// producer-consumer.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct msg{
    int val;
    struct msg *m_next;
};
struct msg *workq = NULL;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void* process_msg(void* argv){
    struct msg *mp;
    for( ; ; ){
        pthread_mutex_lock(&qlock);
        while(workq == NULL)
            pthread_cond_wait(&qready, &qlock);
        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
        int t_val = mp->val;
        free(mp);
        if(t_val == -1) break;
        else printf("%ld: process msg %d\n", time(NULL), t_val);
    }
    return NULL;
}
void enqueue_msg(int val){
    struct msg *mp = malloc(sizeof(struct msg));
    mp->val = val;
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    printf("%ld: %d enqueue\n", time(NULL), val);
    pthread_cond_signal(&qready);
}

int main(){
    pthread_t tid;
    int err = pthread_create(&tid, NULL, process_msg, NULL);
    if(err!=0){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    enqueue_msg(5); enqueue_msg(6);
    sleep(1);
    enqueue_msg(7); enqueue_msg(8);
    sleep(2);
    enqueue_msg(-1);
    void* tret;
    if((err=pthread_join(tid, &tret))!=0){
        fprintf(stderr, "pthread_join error\n"); return 1;
    }
}

