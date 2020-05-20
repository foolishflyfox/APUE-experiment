// mysystem.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int mysystem(const char* cmdstring){
    pid_t pid;
    if(cmdstring==NULL) return 1;
    if(-1==(pid=(fork())))return -1;
    else if(pid==0){
        execl("/bin/sh", "sh", "-c", cmdstring, NULL);
        _exit(127);
    }
    int status;
    if(-1==waitpid(pid, &status, 0)){
        if(errno!=EINTR) return -1;
    }
    return WEXITSTATUS(status);
}
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
    if((status = mysystem(argv[1])) < 0){
        fprintf(stderr, "mysystem(\"%s\") error: %s", 
                        argv[1], strerror(errno));
    }
    pr_exit(status);
}

