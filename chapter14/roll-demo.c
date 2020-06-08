// roll-demo.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFSIZE 511

int main(){
    // 两个描述符都以非阻塞方式打开
    int fd1 = open("t1.pip", O_RDONLY|O_NONBLOCK);
    if(fd1==-1) {perror("open t1.pip error"); exit(1);}
    int fd2 = open("t2.pip", O_RDONLY|O_NONBLOCK);
    if(fd2==-1) {perror("open t2.pip error"); exit(1);}
    int n1, n2;
    char buf1[BUFSIZE+1], buf2[BUFSIZE+1];
    for( ; ; ){
        if((n1 = read(fd1, buf1, BUFSIZ)) > 0){
            buf1[n1] = '\0';
            printf("[t1.pip]:  %s\n", buf1);
        }
        if((n2 = read(fd2, buf2, BUFSIZ)) > 0){
            buf2[n2] = '\0';
            printf("[t2.pip]:  %s\n", buf2);
        }
        usleep(50000);  // 每隔50ms轮询一次
    }
}
