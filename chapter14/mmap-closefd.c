// mmap-closefd.c
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("tmp.txt", O_RDWR);
    if(fd==-1) { perror("open error"); return 1; }
    char* buf = mmap(NULL, 64, PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED==buf) { perror("mmap error"); return 1; }
    if(close(fd)==-1) { perror("close error"); return 1; }
    sleep(1);
    buf[1] = 'x';
}
