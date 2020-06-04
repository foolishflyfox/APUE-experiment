// thread-key-usage.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define bufsize 512
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
static pthread_key_t g_key;
static void destructor(void* ptr){
    printf("run destructor\n");
    free(ptr);
}
static void key_init(){
    pthread_key_create(&g_key, destructor);
}
static void showkey(){
    char* str = pthread_getspecific(g_key);
    printf("%ld: str = %s\n", time(NULL), str==NULL?"NULL":str);
}
static void* foo(void* arg){
    char *str = arg, *buf;
    pthread_once(&init_done, key_init);
    buf = pthread_getspecific(g_key);
    if(arg!=NULL && buf==NULL) {
        buf = malloc(bufsize);
        pthread_setspecific(g_key, buf);
        strncpy(buf, str, bufsize);
    }
    showkey(); sleep(1); showkey();
    return NULL;
}

int main(){
    pthread_t tids[3];
    const char* ss[3] = {"hello", "world", NULL};
    for(int i=0; i<3; i++){
        if(pthread_create(tids+i, NULL, foo, ss[i])){
            fprintf(stderr, "create thread %d error.\n", i); return 1;
        }
    }
    for(int i=0; i<3; i++){
        void* tret;
        if(pthread_join(tids[i], &tret)){
            fprintf(stderr, "join thread %d error.\n", i); return 1;
        }
    }
}
