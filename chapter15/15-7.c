// 15-7.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static int pfd1[2], pfd2[2];
void TELL_WAIT(void){
    if(pipe(pfd1)<0 || pipe(pfd2)<0){
        perror("pipe error"); exit(1);
    }
}
void TELL_PARENT(pid_t pid){
    if(write(pfd2[1], "c", 1) != 1){
        perror("write error"); exit(1);
    }
}
void WAIT_CHILD(void){
    char c;
    if(read(pfd2[0], &c, 1)!=1){
        perror("read error"); exit(1);
    }
    if(c!='c') {
        fprintf(stderr, "WAIT_CHILD: incorrect data"); exit(1);
    }
}
void TELL_CHILD(pid_t pid){
    if(write(pfd1[1], "p", 1)!=1){
        perror("write error"); exit(1);
    }
}
void WAIT_PARENT(void){
    char c;
    if(read(pfd1[0], &c, 1)!=1){
        perror("read error"); exit(1);
    }
    if(c!='p'){
        fprintf(stderr, "WAIT_PARENT: incorrect data"); exit(1);
    }
}

int main(){
    TELL_WAIT();
    pid_t pid = fork();
    if(pid<0){
        perror("fork error"); exit(1);
    }
    if(pid){  // parent
        printf("%ld: parent 2\n", time(NULL));
        sleep(1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        printf("%ld: parent 2\n", time(NULL));
    }else{  // child
        char c;
        WAIT_PARENT();
        printf("%ld: child\n", time(NULL));
        sleep(1);
        TELL_PARENT(getppid());
    }
}

