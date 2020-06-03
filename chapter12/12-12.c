// 12-12.c
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

// #define MAXSTRINGSZ 4096
#define GETTIMES 5000
// static char envbuf[MAXSTRINGSZ];
extern char **environ;
pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
static void thread_init(void){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}
int mygetenv_r(const char* name, char *buf, int buflen){
    pthread_once(&init_done, thread_init);
    int len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for(int i=0; environ[i]!=NULL; i++){
        if((strncmp(name, environ[i], len)==0) && environ[i][len] == '='){
            int olen = strlen(&environ[i][len+1]);
            if(olen >= buflen){
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf, &environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}
void* foo(void* arg){
    char buf[128];
    for(int i=0; i<GETTIMES; ++i){
        mygetenv_r("A", buf, 128);
        printf("%s\n", buf);
    }
    return NULL;
}
int main(){
    pthread_t tid;
    char buf[128];
    if(pthread_create(&tid, NULL, foo, NULL)){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    for(int i=0; i<GETTIMES; ++i){
        mygetenv_r("B", buf, 128);
         printf("%s\n", buf);
    }
    void* tret;
    if(pthread_join(tid, &tret)){
        fprintf(stderr, "pthread_join error\n"); return 1;
    }
}

