// job-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show_ids(){
    fprintf(stderr, "pid = %d, ppid = %d, pgid = %d, sid = %d\n", 
            getpid(), getppid(), getpgrp(), getsid(getpid()));
}

int main(){
    pid_t pid;
    if(-1==(pid=fork())){
        perror("fork error"); return 1;
    }else if(pid==0){
        show_ids();
        while(1) sleep(5);
    }else{
        show_ids();
        while(1) sleep(5);
        wait(NULL);
    }
}
