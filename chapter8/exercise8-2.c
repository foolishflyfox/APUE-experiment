// exercise8-2.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_v = 5;

void foo(){
    int foo_v = 15;
    pid_t pid;
    if(-1==(pid = vfork())){
        perror("vfork error"); _exit(1);
    }else if(pid==0){
        global_v *= 10;
        foo_v *= 10;
    }else{
        printf("child pid = %d\n", pid);
        if(-1==waitpid(pid, NULL, 0)){
            perror("waitpid error"); _exit(1);
        }
    }
    printf("(%d): foo_v = %d\n", getpid(), foo_v);
}

int main(){
    int main_v = 10;
    foo();
    printf("(%d): main_v = %d, global_v = %d\n", 
        getpid(), main_v, global_v);
}
