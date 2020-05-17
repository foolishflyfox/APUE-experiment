// pr_exit.c
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

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

int main(){
    pid_t pid;
    int status;
    if((pid = fork())<0){ perror("1 fork error");}
    else if(pid==0){ exit(7); }
    if(wait(&status)!=pid) perror("1 wait error");
    pr_exit(status);

    if((pid = fork())<0) { perror("2 fork error"); }
    else if(pid==0) {abort();}
    if(wait(&status)!=pid) perror("2 wait error");
    pr_exit(status);

    if((pid = fork())<0) { perror("3 fork error"); }
    else if(pid==0) {status /= 0;}
    if(wait(&status)!=pid) perror("3 wait error");
    pr_exit(status);
}
