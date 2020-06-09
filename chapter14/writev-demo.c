// writev-demo.c
#include <stdio.h>
#include <sys/uio.h>
#include <fcntl.h>

int main(){
    struct iovec vecs[3];
    int fd = open("tmp.txt", O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if(fd == -1) { perror("open error"); return 1; }
    vecs[0].iov_base = "bb"; vecs[0].iov_len = 2;
    vecs[1].iov_base = "ccc"; vecs[1].iov_len = 3;
    vecs[2].iov_base = "a\n"; vecs[2].iov_len = 2;
    int n = writev(fd, vecs, sizeof(vecs)/sizeof(*vecs));
    printf("write %d bytes\n", n);
}
