// 8-20.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    if((pid=fork()) < 0){
        perror("fork error"); return 1;
    }else if(pid==0){
        if(execl("/tmp/testinterp", "testinterp", "myarg1",
                    "MY ARG2", NULL) < 0){
            perror("execl error"); return 1;
        }
    }
    if(waitpid(pid, NULL, 0) < 0){
        perror("waitpid error"); return 1;
    }
}
