// signal-unsafe.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

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
void sig_alrm(int signo){
    foo("sig_alrm");
}
int main(){
    if(signal(SIGALRM, sig_alrm)==SIG_ERR){
        fprintf(stderr, "signal(SIGALRM) error\n"); return 1;
    }
    alarm(1);
    foo("main");
    printf("end of main.\n");
}


