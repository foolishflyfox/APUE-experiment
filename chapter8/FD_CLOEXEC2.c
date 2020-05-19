// FD_CLOEXEC2.c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd = open("tmp", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd==-1){
        perror("open error"); return 1;
    }
#ifdef SET_CLOEXEC
    fputs("set FD_CLOEXEC\n", stdout);
    int flags = fcntl(fd, F_GETFD);
    if(fcntl(fd, F_SETFD, (flags|FD_CLOEXEC))==-1){
        perror("fcntl error"); return 1;
    }
#endif
    char s_fd[16]; sprintf(s_fd, "%d", fd);
    char* t_argv[] = {"./write-hw.out", s_fd, NULL};
    if(execv(t_argv[0], t_argv)==-1){
        perror("execv error");
    }
}
