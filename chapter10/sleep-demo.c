// sleep-demo.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static void sig_alrm(int signo){
    printf("%ld: received SIGALRM\n", time(NULL));
    sleep(4);
    printf("%ld: exit sig_alrm\n", time(NULL));
}
int main(){
    if(SIG_ERR==signal(SIGALRM, sig_alrm)){
        perror("signal(SIGALRM) error"); return 1;
    }
    printf("t0: %ld\n", time(NULL));
    alarm(3);
    unsigned int rt = sleep(10);
    printf("%ld: rt = %u\n", time(NULL), rt);
}
