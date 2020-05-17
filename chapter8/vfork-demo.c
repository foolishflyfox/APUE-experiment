// vfork-demo.c
#include <stdio.h>
#include <unistd.h>

int globvar = 6;

int main(){
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if((pid=vfork()) < 0){
        perror("vfork error");
    }else if(pid==0){
        globvar++;
        var++;
        _exit(0);
    }
    printf("pid=%ld, glob=%d, var=%d\n", (long)getpid(), globvar, var);
}

