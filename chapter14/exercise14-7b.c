// exercise14-7b.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int cnt = 0;
    int fd = open("tmp.pip", O_RDWR|O_NONBLOCK); // O_WRONLY|O_NONBLOCK将出错
    if(fd==-1) { perror("open error"); return 1; }
    while(write(fd, "a", 1)==1){ ++cnt;}
    printf("cnt = %d\n", cnt);
}

