// setsid-getsid.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show_ids(const char* prefix){
    printf("%s: pid=%d, pgid=%d\n", prefix, getpid(), getpgrp());
}
int main(){
    pid_t pid, sid;
    if(-1==(pid=fork())){
        perror("fork error"); return 1;
    }else if(pid==0){
        show_ids("child");
        if(-1==(sid=setsid())){
            perror("child setsid error"); return 1;
        }
        printf("child sid = %d\n", sid);
        show_ids("child");
    }else{
        show_ids("parent");
        if(-1==(sid=setsid())){
            perror("parent setsid error");
        }else{
            printf("parent sid = %d\n", sid);
            show_ids("parent");
        }
        waitpid(pid, NULL, 0);
    }
}
