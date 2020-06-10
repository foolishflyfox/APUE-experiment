// 14-23-writev.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(){
    char buf1[100], buf2[200];
    int fd = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd == -1) { perror("open error"); return 1; }
    struct iovec iov[2];
    iov[0].iov_base = buf1; iov[0].iov_len = 100;
    iov[1].iov_base = buf2; iov[1].iov_len = 200;
    for(int i = 1048576; i > 0; --i) 
        if(writev(fd, iov, 2)!=300){ perror("writev error"); return 1;}
    close(fd);
}

