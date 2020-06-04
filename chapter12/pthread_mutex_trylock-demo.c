// pthread_mutex_trylock-demo.c
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int main(){
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    int err = pthread_mutex_lock(&lock);
    if(err) fprintf(stderr, "1 lock error: %s\n", strerror(err));
    err = pthread_mutex_trylock(&lock);
    if(err) fprintf(stderr, "1 trylock error: %s\n", strerror(err));
    err = pthread_mutex_unlock(&lock);
    if(err) fprintf(stderr, "1 unlock error: %s\n", strerror(err));
    err = pthread_mutex_trylock(&lock);
    if(err) fprintf(stderr, "2 trylock error: %s\n", strerror(err));
    err = pthread_mutex_trylock(&lock);
    if(err) fprintf(stderr, "3 trylock error: %s\n", strerror(err));
}

