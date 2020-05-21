// 8-24.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void pr_exit(int status){
    if(WIFEXITED(status)){
        printf("normal termination, exit status is %d\n",
            WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
        printf("abnormal termination, signal number is %d %s\n",
            WTERMSIG(status), 
            #ifdef WCOREDUMP
                WCOREDUMP(status)?",core file generated": ",no core file"
            #else
                ""
            #endif    
            );
    }else if(WIFSTOPPED(status)){
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    }
}

int main(int argc, char* argv[]){
    int status;
    if(argc!=2){
        fprintf(stderr, "Usage: %s <cmd>\n", argv[0]);
        return 1;
    }
    printf("real uid = %u, effective uid = %u\n", getuid(), geteuid());
    if((status = system(argv[1])) < 0){
        fprintf(stderr, "system(\"%s\") error: %s", 
                        argv[1], strerror(errno));
    }
    pr_exit(status);
}
