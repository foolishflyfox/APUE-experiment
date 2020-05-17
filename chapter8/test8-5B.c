// test8-5B.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    if(fork()==0){
        sleep(10);
        printf("child process finished\n");
    }else{
        sleep(20);
        printf("deal with child process\n");
        int wstatus; wait(&wstatus);
        sleep(10);
    }
}
