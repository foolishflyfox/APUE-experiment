// 12-11.c
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAXSTRINGSZ 4096
#define GETTIMES 5000
static char envbuf[MAXSTRINGSZ];
extern char **environ;

char* mygetenv(const char* name){
    int len = strlen(name);
    for(int i=0; environ[i]!=NULL; i++){
        if((strncmp(name, environ[i], len)==0) && environ[i][len] == '='){
            strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
            return envbuf;
        }
    }
    return NULL;
}
void* foo(void* arg){
    for(int i=0; i<GETTIMES; ++i){
        printf("%s\n", mygetenv("A"));
    }
    return NULL;
}
int main(){
    pthread_t tid;
    if(pthread_create(&tid, NULL, foo, NULL)){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    for(int i=0; i<GETTIMES; ++i){
        printf("%s\n", mygetenv("B"));
    }
    void* tret;
    if(pthread_join(tid, &tret)){
        fprintf(stderr, "pthread_join error\n"); return 1;
    }
}

