// readv-demo.c
#include <stdio.h>
#include <sys/uio.h>
#include <fcntl.h>

int main(){
    int fd = open("tmp.txt", O_RDONLY);
    if(fd==-1) { perror("open error"); return 1; }
    char buf1[3] = {0}, buf2[4] = {0}, buf3[5] = {0};
    struct iovec vecs[3];
    vecs[0].iov_base = buf1; vecs[0].iov_len = 2;  // 保留 `\0`
    vecs[1].iov_base = buf2; vecs[1].iov_len = 3;
    vecs[2].iov_base = buf3; vecs[2].iov_len = 4;
    int n = readv(fd, vecs, 3);
    printf("n = %d\n1: %s\n2: %s\n3: %s\n", n, buf1, buf2, buf3);
}
