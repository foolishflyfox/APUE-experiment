// longjmp-diff.c
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf jmp_env;

void deal_quit(int signo){
    printf("received SIGQUIT\n");
    sleep(3);
    printf("exit deal_quit\n");
    siglongjmp(jmp_env, 1);
}

int main(){
    if(SIG_ERR == signal(SIGQUIT, deal_quit)){
        perror("signal error"); return 1;
    }
#ifdef SAVEMASK
    sigsetjmp(jmp_env, 1);
#else
    sigsetjmp(jmp_env, 0);
#endif
    pause();
}
