// write-hw.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc<2){
        fprintf(stderr, "Usage: %s <fd>\n", argv[0]); return 1;
    }
    int fd = atoi(argv[1]);
    if(write(fd, "hello,world\n", 12)==-1)
        perror("write error");
    printf("dup(STDOUT_FILENO) = %d\n", dup(STDOUT_FILENO));
}

