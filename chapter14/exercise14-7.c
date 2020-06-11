// exercise14-7.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>

void showvar(const char* nm, long var) { printf("%s = %ld\n", nm, var); }
#define SHOWVAR(var) showvar(#var, (long)(var))
int main(){
    int fds[2];
    SHOWVAR(_POSIX_PIPE_BUF);
    SHOWVAR(PIPE_BUF);
    if(pipe(fds)==-1) { perror("pipe error"); exit(1); }
    int pid = fork();
    if(pid == -1) { perror("fork error"); exit(1); }
    if(pid){
        waitpid(pid, NULL, 0);
    }else{
        int flags = fcntl(fds[1], F_GETFL, 0);
        if(flags < 0){ perror("fcntl(F_GETFL) error"); exit(1); }
        flags |= O_NONBLOCK;
        if(fcntl(fds[1], F_SETFL, flags) < 0){ 
            perror("fcntl(F_SETFL) error"); exit(1);
        }
        SHOWVAR(fpathconf(fds[1], _PC_PIPE_BUF));
        int cnt = 0;
        while(write(fds[1], "a", 1)==1){
            ++cnt;
        }
        printf("cnt = %d\n", cnt);
    }
}
