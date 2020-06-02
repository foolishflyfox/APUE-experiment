// pthread_limits.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void printconf(const char* confname, int confcode){
    printf("%s = %ld\n", confname, sysconf(confcode));
}
#define PRINTCONF(conf) printconf(#conf, conf)

int main(){
    PRINTCONF(_SC_THREAD_DESTRUCTOR_ITERATIONS);
    PRINTCONF(_SC_THREAD_KEYS_MAX);
    PRINTCONF(_SC_THREAD_STACK_MIN);
    PRINTCONF(_SC_THREAD_THREADS_MAX);
}
