// multi-fgp.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    pid_t pid;
    char buf[128];
    if(-1==(pid=fork())){
        perror("fork error"); return 1;
    }else if(0==pid){
        #ifdef PARENT_FIRST
        sleep(1);
        #endif
        if(NULL==fgets(buf, sizeof(buf), stdin)){
            perror("child fgets error"); return 1;
        }else printf("child: %s", buf);
    }else{
        #ifdef CHILD_FIRST
        sleep(1);
        #endif
        if(NULL==fgets(buf, sizeof(buf), stdin)){
            perror("parent fgets error"); return 1;
        }else printf("parent: %s", buf);
        wait(NULL);
    }
}
