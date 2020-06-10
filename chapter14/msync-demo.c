// msync-demo.c
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd = open("tmp.txt", O_RDWR);
    if(fd == -1) { perror("open error"); return 1; }
    char* buf = mmap(NULL, 64, PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == buf){
        perror("mmap error"); return 1;
    }
    buf[1] = 'x', buf[3] = 'y', buf[5] = 'z';
    sleep(10);
    if(-1 == msync(buf, 3, MS_SYNC)){
        perror("msync error"); return 1;
    }
}
