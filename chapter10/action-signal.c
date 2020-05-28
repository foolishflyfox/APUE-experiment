// action-signal.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static sigset_t newsigs, oldsigs;
static void sig_quit(int signo){
    printf("\t%ld: running sig_tstp\n", time(NULL));
}
static void sig_tstp(int signo){
    printf("\t%ld: enter sig_tstp\n", time(NULL));
    sleep(10);
    sigprocmask(SIG_SETMASK, &oldsigs, NULL);
    sleep(5);
    printf("\t%ld: exit sig_tstp\n", time(NULL));
}

int main(){
    if(SIG_ERR==signal(SIGTSTP, sig_tstp)){
        perror("signal(SIGTSTP) error"); return 1;
    }
    if(SIG_ERR==signal(SIGQUIT, sig_quit)){
        perror("signal(SIGQUIT) error"); return 1;
    }
    sigemptyset(&newsigs);
    sigaddset(&newsigs, SIGQUIT);
    sigprocmask(SIG_BLOCK, &newsigs, &oldsigs);
    for(; ;) pause();
}
