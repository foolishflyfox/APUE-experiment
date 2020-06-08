// pipe-client.c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFSIZE 512

int main(){
    char buf[BUFSIZE];
   int fd = open("tmp.pip", O_WRONLY);
    if(fd == -1) {
        perror("open error"); return 1;
    }
    while(NULL!=fgets(buf, BUFSIZE, stdin)){
        int n = strlen(buf);
        write(fd, buf, n-1);    // 不发送最后的 \n
    }
}

