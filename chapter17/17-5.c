// 17-5.c
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

int main(void){
    int fd, size;
    struct sockaddr_un un;
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, "foo.socket");
    if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
        perror("socket error"); exit(1);
    }
    size = offsetof(struct sockaddr_un, sun_path)+strlen(un.sun_path);
    // bind 之后会创建套接字文件类型的文件：foo.socket
    if(bind(fd, (struct sockaddr*)&un, size) < 0){
        perror("bind error"); exit(1);
    }
    printf("UNIX domain socket bound\n");
}
