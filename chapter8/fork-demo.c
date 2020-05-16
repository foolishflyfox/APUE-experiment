// fork-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(){
    int var;
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1)!=sizeof(buf)-1)
        perror("write error");
    printf("before fork\n");
    if((pid=fork()) < 0){
        perror("fork error");
    }else if(pid==0){
        globvar++;
        var++;
    }else{
        sleep(2);
    }
    printf("pid=%ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
}

