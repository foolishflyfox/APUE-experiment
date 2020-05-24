// exercise9-2.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show_ids(const char* prefix){
    // tcpgrp 为拥有控制终端的进程组ID
    fprintf(stderr, "%s: pid=%d, ppid=%d, pgid=%d, sid=%d, tcpgrp=%d\n", 
            prefix, getpid(), getppid(), getpgrp(), 
            getsid(getpid()), tcgetpgrp(STDIN_FILENO));
}

int main(){
    pid_t pid = fork();
    if(pid==-1){
        perror("fork error"); return 1;
    }else if(pid==0){
        show_ids("child 1");
        if(setsid()==-1){
            perror("setsid error"); return 1;
        }
        show_ids("child 2");
    }else{
        show_ids("parent");
        wait(NULL);
    }
}
