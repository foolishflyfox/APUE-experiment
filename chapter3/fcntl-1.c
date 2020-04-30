// fcntl-1.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <descriptor>\n", argv[0]); return 1;
    }
    int fd = atoi(argv[1]);
    int val = fcntl(fd, F_GETFL);
    if(val<0){
        fprintf(stderr, "fcntl error\n"); return 1;
    }
    int accmod = val & O_ACCMODE;
    if(accmod==O_RDONLY) printf("%d read only; ", fd);
    else if(accmod==O_WRONLY) printf("%d write only; ", fd);
    else if(accmod==O_RDWR) printf("%d read write; ", fd);
    if(val & O_APPEND) printf("append;");
    printf("\n");
    // 对除0、1、2描述符以外的描述符进行操作
    if(fd>2){
        if(accmod==O_RDONLY || accmod==O_RDWR){
            char c; 
            read(fd, &c, 1);
            printf("read '%c' from %d\n", c, fd);
        }
        if(accmod==O_WRONLY || accmod==O_RDWR)
            write(fd, "&\n", 2);
    }
}


