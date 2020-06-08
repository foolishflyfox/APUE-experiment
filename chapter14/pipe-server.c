// pipe-server.c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 511

int main(){
    char buf[BUFSIZE+1];
    int n;
    int fd = open("tmp.pip", O_RDONLY);
    if(fd == -1) {
        perror("open error"); return 1;
    }
    while((n = read(fd, buf, BUFSIZE)) > 0){
        buf[n] = '\0';
        printf("%d received: %s\n", getpid(),buf);
    }
}
