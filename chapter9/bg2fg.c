// bg2fg.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void deal_sign(int sig){
    if(sig==SIGTTIN){
        printf("receive SIGTTIN\n");
    }else if(sig==SIGCONT){
        printf("receive SIGCONT\n");
    }else{
        printf("receive signal\n");
    }
}

int main(int argc, char* argv[]){
    sigset(SIGTTIN, deal_sign);
    sigset(SIGCONT, deal_sign);
    char buf[128];
    int cnt = 0;
    if(-1==(cnt = read(STDIN_FILENO, buf, sizeof(buf)))){
        perror("read error"); return 1;
    }else{
        buf[cnt] = '\0';
        printf("%s get \"%s\"\n", argv[0], buf);
    }
}
