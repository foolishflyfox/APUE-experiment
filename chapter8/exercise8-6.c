// exercise8-6.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t p;
    if(-1==(p=fork())){
        perror("fork p error"); return 1;
    }else if(p==0){
        exit(0);
    }
    char cmd[128];
    sprintf(cmd, "ps -o pid,stat -p %d", p);
    sleep(1);
    if(-1==system(cmd)){
        perror("system error"); exit(1);
    }
}
