// 11-10.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct foo{
    int f_count;
    pthread_mutex_t flock;
    int f_id;
    /* ... more stuff here ... */
};
// allocate the object
struct foo* foo_allock(int id){
    struct foo *fp;
    if((fp = malloc(sizeof(struct foo))) != NULL){
        fp->f_count = 1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->flock, NULL) != 0){
            free(fp);
            return NULL;
        }
        /* ... continue initialization ... */
    }
    return fp;
}
void foo_hold(struct foo* fp){
    pthread_mutex_lock(&fp->flock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->flock);
}
void foo_rele(struct foo* fp){
    pthread_mutex_lock(&fp->flock);
    if(--fp->f_count == 0){ /* last reference */
        pthread_mutex_unlock(&fp->flock);
        pthread_mutex_destroy(&fp->flock);
        free(fp);
    }else{
        pthread_mutex_unlock(&fp->flock);
    }
}
