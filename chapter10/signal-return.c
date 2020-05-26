// signal-return.c
#include <stdio.h>
#include <signal.h>

typedef void Sigfunc(int);
void deal_signo(int v){}
void show_action(const char* prefix, Sigfunc* func){
    if(func==SIG_IGN){
        printf("%s: %s\n", prefix, "SIG_IGN");
    }else if(func==SIG_DFL){
        printf("%s: %s\n", prefix, "SIG_DFL");
    }else if(func==SIG_ERR){
        printf("%s: %s\n", prefix, "SIG_ERR");
    }else{
        printf("%s: %p\n", prefix, func);
    }
}

int main(){
    Sigfunc* func;
    printf("deal_signo address: %p\n", deal_signo);
    func = signal(SIGABRT, SIG_IGN);
    show_action("0 action", func);
    func = signal(SIGABRT, deal_signo);
    show_action("1 action", func);
    func = signal(SIGABRT, SIG_DFL);
    show_action("2 action", func);
    func = signal(-1, NULL);
    show_action("3 action", func);
}
