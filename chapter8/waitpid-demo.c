// waitpid-demo.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

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
    waitpid(p1, &x, 0); printf("%d exit\n", WEXITSTATUS(x));
    waitpid(p2, &x, 0); printf("%d exit\n", WEXITSTATUS(x));
    waitpid(p3, &x, 0); printf("%d exit\n", WEXITSTATUS(x));
}

