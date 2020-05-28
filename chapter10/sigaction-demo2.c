// sigaction-demo2.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
static void sig_deal(int signo){
    printf("received %d\n", signo);
}
int main(){
    struct sigaction action;
    sigaction(SIGQUIT, NULL, &action);
    action.sa_handler = sig_deal;
    //action.sa_flags &= ~SA_RESTART;
    sigaction(SIGQUIT, &action, NULL);
    char c;
    if(read(STDIN_FILENO, &c, 1)<1){
        perror("read error");
    }
    printf("end of main\n");
}

