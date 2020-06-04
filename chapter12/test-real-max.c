// test-real-max.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef KEYS_CNT
#define KEYS_CNT 2048
#endif

int main(){
    pthread_key_t keys[KEYS_CNT];
    for(int i=0; i<KEYS_CNT; ++i) {
        if(pthread_key_create(keys+i, NULL)){
            fprintf(stderr, "create key %d error\n", i); return 1;
        }
        void* c = malloc(1);
        pthread_setspecific(keys[i], c);
    }
}
