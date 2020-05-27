// abort-demo3.c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
static jmp_buf env;
static void sig_abrt(int signo){
    printf("received SIGABRT\n");
    siglongjmp(env, 1);
}
int main(){
    if(SIG_ERR==signal(SIGABRT, sig_abrt)){
        perror("signal(SIGABRT) error");
    }
    sleep(1);
    if(sigsetjmp(env, 1)==0) abort();
    printf("end of main\n");
}
