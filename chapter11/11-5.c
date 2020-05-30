// 11-5.c
#include <stdio.h>
#include <pthread.h>

void cleanup(void* arg){
    printf("cleanup: %s\n", (char*)arg);
}
void* thr_fn1(void* arg){

}
void* thr_fn2(void* arg){

}

int main(){
    int err;
    pthread_t tid1, tid2;
    void *tret;
    
}
