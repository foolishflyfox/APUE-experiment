// signal-samesig.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void deal_quit(int signo){
    printf("start deal_quit\n");
    sleep(10);
    printf("exit deal_quit\n");
}

int main(){
    if(SIG_ERR==(signal(SIGQUIT, deal_quit))){
        perror("signal error"); return 1;
    }
    for(;;) sleep(1);
}


