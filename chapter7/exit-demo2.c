// exit-demo2.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: %s <return|exit|_Exit|_exit>\n", argv[0]);
        return 1;
    }
    if(strcmp(argv[1], "return")==0){
        int fd = open("tmp.1", O_CREAT|O_TRUNC|O_WRONLY, 0644);
        write(fd, "test return\n", 12);
    }else if(strcmp(argv[1], "exit")==0){
        int fd = open("tmp.2", O_CREAT|O_TRUNC|O_WRONLY, 0644);
        write(fd, "test exit\n", 10);
        exit(0);
    }else if(strcmp(argv[1], "_exit")==0){
        int fd = open("tmp.3", O_CREAT|O_TRUNC|O_WRONLY, 0644);
        write(fd, "test _exit\n", 11);
        _exit(0);
    }else if(strcmp(argv[1], "_Exit")==0){
        int fd = open("tmp.4", O_CREAT|O_TRUNC|O_WRONLY, 0644);
        write(fd, "test _Exit\n", 11);
        _Exit(0);
    }
    return 0;
}

