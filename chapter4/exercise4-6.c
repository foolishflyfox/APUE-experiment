// exercise4-6.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]);
        return 1;
    }
    int fd_src, fd_dst;
    if((fd_src=open(argv[1], O_RDONLY))==-1){
        fprintf(stderr, "open %s error: %s\n", argv[1], strerror(errno));
        return 1;
    }
    if((fd_dst=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644))==-1){
        fprintf(stderr, "open %s error: %s\n", argv[2], strerror(errno));
        return 1;
    }
    int v = 0;
    char c;
    while((v=read(fd_src, &c, 1))>0){
        if(c){
            if(write(fd_dst, &c, 1)==-1){
                perror("write error"); return 1;
            }
        }
    }
    if(v==-1){
        perror("read error"); return 1;
    }
    return 0;
}
