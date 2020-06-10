// mmap-demo.c
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#ifndef MAP_FLAG
#define MAP_FLAG MAP_SHARED 
#endif
int main(){
    int fd = open("tmp.txt", O_RDWR);
    if(fd==-1){ perror("open error"); return 1; }
    // 由于 len = 5，并不是页大小的整数倍，因此扩展到一个页
    char* buf = mmap(NULL, 5, PROT_READ|PROT_WRITE, MAP_FLAG, fd, 0);
    if(buf==MAP_FAILED){ perror("mmap error"); return 1; }
    printf("%s\n", buf);
    snprintf(buf+2, 11, "1234567890");
}
