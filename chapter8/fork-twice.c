// fork-twice.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    if((pid=fork()) < 0){
        perror("first fork error");
    }else if(pid==0){
        if((pid=fork()) < 0){
            perror("second fork error");
        }else if(pid>0){
            exit(0);
        }else{
            sleep(2);
            printf("second child, parent pid = %ld\n", (long)getppid());
            exit(0);
        }
    }
    if(waitpid(pid, NULL, 0)!=pid) perror("waitpid error");
    return 0;
}
