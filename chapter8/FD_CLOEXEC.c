// FD_CLOEXEC.c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <fd>", argv[0]);
        return 1;
    }
    int fd = atoi(argv[1]);
#ifdef SET_CLOEXEC
    fputs("set FD_CLOEXEC\n", stdout);
    int flags = fcntl(fd, F_GETFD);
    if(fcntl(fd, F_SETFD, (flags|FD_CLOEXEC))==-1){
        perror("fcntl error"); return 1;
    }
#endif
    char* t_argv[] = {"./write-hw.out", argv[1], NULL};
    if(execv(t_argv[0], t_argv)==-1){
        perror("execv error");
    }
}
