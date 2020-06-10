// 14-23-write1.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    char buf1[100], buf2[200];
    char buf3[300];
    int fd = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd == -1) { perror("open error"); return 1; }
    for(int i = 1048576; i > 0; --i) {
        memcpy(buf3, buf1, 100);
        memcpy(buf3+100, buf2, 200);
        if(write(fd,buf3,300)!=300){ perror("write error"); return 1;}
    }
    close(fd);
}
