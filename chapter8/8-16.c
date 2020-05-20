// 8-16.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char* env_init[] = {"USER=unknown", "PATH=/home", NULL};

int main(){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("first fork error"); return 1;
    }else if(pid==0){
        if(execle("/tmp/echoall", "echoall", "myarg1",
                "MY ARG2", NULL, env_init) <0){
            perror("execle error"); return 1;
        }
    }
    if(waitpid(pid, NULL, 0)<0){
        perror("wait error"); return 1;
    }
    if((pid = fork()) < 0){
        perror("second fork error"); return 1;
    }else if(pid==0){
        if(execlp("echoall", "echoall", "only 1 arg", NULL)<0){
            perror("execlp error");
        }
    }
}
