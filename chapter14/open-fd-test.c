// open-fd-test.c
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int fd1 = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd1 == -1) {
        perror("open tmp.txt error"); return 1;
    }
    int fd2 = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(write(fd1, "aaaaaaaa", 8)!=8) {
        perror("write aaaaaaaa error"); return 1;
    }
    if(write(fd2, "bb", 2)!=2) {
        perror("write bb error"); return 1;
    }
    if(close(fd1)==-1) {
        perror("close fd1 error"); return 1;
    }
    if(write(fd2, "cc\n", 3)!=3) {
        perror("write cc error"); return 1;
    }
}
