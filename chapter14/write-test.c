// write-test.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BSZ 10000000
int main(){
    int fd = open("tmp.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd==-1) {
        perror("open error"); return 1;
    }
    char buf[BSZ];
    printf("%zd\n", write(fd, buf, BSZ));
}

