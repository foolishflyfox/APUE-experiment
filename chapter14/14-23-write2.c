// 14-23-write2.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    char buf1[100], buf2[200];
    int fd = open("tmp.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd == -1) { perror("open error"); return 1; }
    for(int i = 1048576; i > 0; --i) {
        if(write(fd,buf1,100)!=100){ perror("write 1 error"); return 1;}
        if(write(fd,buf2,200)!=200){ perror("write 2 error"); return 1;}
    }
    close(fd);
}
