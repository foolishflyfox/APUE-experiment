// thread-safe.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t glock = PTHREAD_MUTEX_INITIALIZER;
int g_value = 10;
void* foo(void* argc){
    pthread_mutex_lock(&glock);
    printf("start %s: g_value = %d\n", (char*)argc, g_value);
    g_value += 1;
    sleep(2);
    printf("end %s: g_value = %d\n", (char*)argc, g_value);
    pthread_mutex_unlock(&glock);
    return NULL;
}
int main(){
    pthread_t tid;
    void* tret;
    if(pthread_create(&tid, NULL, foo, "sub thread")){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    foo("main thread");
    if(pthread_join(tid, &tret)){
        fprintf(stderr, "pthread_join error\n"); return 1;
    }
}


