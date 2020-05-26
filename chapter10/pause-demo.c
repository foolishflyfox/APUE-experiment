// pause-demo.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void deal_signal(int signo){
    printf("received %d\n", signo);
    sleep(3);
    printf("exit deal_signal\n");
}

int main(){
    if(SIG_ERR == signal(SIGALRM, deal_signal)){
        perror("signal error"); return 1;
    }
    alarm(2);
    int ret =  pause();
    printf("ret = %d, errno = %d\n", ret, errno);
}
