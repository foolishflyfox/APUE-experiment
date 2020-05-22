// tcsetpgrp-demo.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    int fd = open("/dev/tty", O_RDWR);
    if(-1==fd){
        perror("open error"); return 1;
    }
    pid_t pid = atoi(argv[1]);
    if(-1==tcsetpgrp(fd, pid)){
        perror("tcsetpgrp error"); return 1;
    }
    sleep(10);
}
