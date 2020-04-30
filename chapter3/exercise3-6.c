// exercise3-6.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int fd = open("tmp", O_RDWR|O_APPEND);
    char c = 0;
    int n = 0;

    lseek(fd, 3, SEEK_SET);
    if((n=read(fd, &c, 1))==-1) printf("read1 error\n");
    else printf("read1 read %d char: '%c'\n", n, c);

    c=0;
    if((n=read(fd, &c, 1))==-1) printf("read2 error\n");
    else printf("read2 read %d char: '%c'\n", n, c);

    lseek(fd, 6, SEEK_SET);
    write(fd, "X\n", 2);
    
    c = 0;
    if((n=read(fd, &c, 1))==-1) printf("read3 error\n");
    else printf("read2 read %d char: '%c'\n", n, c);
    close(fd);
}

