// waitpid-demo2.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t p1, p2, p3;
    if((p1=fork())==0){
        sleep(3);
        exit(1);
    }
    if((p2=fork())==0){
        sleep(2);
        exit(2);
    }
    if((p3=fork())==0){
        sleep(1);
        exit(3);
    }
    int x;
    while(waitpid(-1, &x, 0)!=-1)
        printf("%d exit\n", WEXITSTATUS(x));
}

