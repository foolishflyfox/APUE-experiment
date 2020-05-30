// thread-inc.c
#include <stdio.h>
#include <pthread.h>
#define N 10000

int v = 0;
void* add_N(void* arg){
    for(int i=0; i<N; ++i) v++;
    return NULL;
}

int main(){
    pthread_t tid;
    void* tret;
    int err = pthread_create(&tid, NULL, add_N, NULL);
    if(err!=0){
        fprintf(stderr, "error %d: pthread_create error\n", err);
        return 1;
    }
    for(int i=0; i<N; ++i) v++;
    if((err = pthread_join(tid, &tret))!=0){
        fprintf(stderr, "error %d: pthread_join error\n", err);
        return 1;
    }
    printf("v = %d\n", v);
}


