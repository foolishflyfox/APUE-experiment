// kill0.c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    pid_t pid = atoi(argv[1]);
    if(-1==kill(pid, 0)){
        perror("kill error");
    }else{
        printf("Find process %d.\n", pid);
    }
}

