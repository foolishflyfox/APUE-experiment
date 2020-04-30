// lseek.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int fd = open("test.txt", O_RDWR);
    char buf[10]; 
    write(fd, "ABC", 3);
    // 查看定位函数的输出
    printf("%lld\n", lseek(fd, 2, SEEK_CUR));
    read(fd, buf, 2); buf[2] = 0;
    printf("%s\n", buf);
    lseek(fd, 20, SEEK_END);
    write(fd, "xx", 2);
    close(fd);
}

