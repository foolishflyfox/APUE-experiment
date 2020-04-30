// setfl-1.c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int fd = atoi(argv[1]);
    int flag = fcntl(fd, F_GETFL);
    printf("fd flag is 0x%x\n", flag);
    flag = (flag & ~O_ACCMODE)|O_RDWR;
    printf("change to 0x%x\n", flag);
    printf("F_SETFL return is %d\n", fcntl(fd, F_SETFL, flag));
    printf("fd falg is 0x%x\n", fcntl(fd, F_GETFL));
}

