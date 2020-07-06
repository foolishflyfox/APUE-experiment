// connect-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BSZ 255
#define SERVER_PORT 60000
#define CLIENT_PORT 60010

int main(){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SERVER_PORT);
    char msg[BSZ+1] = {0};
    pid_t pid = fork();
    if(pid == -1) { perror("fork error"); exit(1); }
    if(pid == 0){
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd == -1) { perror("server socket error");  exit(1); }
        if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
            perror("bind error"); exit(1);
        }
        if(listen(fd, 32) < 0){ perror("listen error"); exit(1); }
        socklen_t addrlen = sizeof(addr);
        int client = accept(fd, (struct sockaddr*)&addr, &addrlen);
        if(client < 0){
            perror("accept error"); exit(1);
        }
        // 打印客户端信息
        char buf[INET_ADDRSTRLEN] = {0};
        printf("Client Info: %s:%d\n",
            inet_ntop(AF_INET, &addr.sin_addr.s_addr, buf, INET_ADDRSTRLEN),
            ntohs(addr.sin_port));
        // 向客户端发送/接收数据
        if(write(client, "hello", 5)!=5) perror("write error");
        if(read(client, msg, BSZ)<0) perror("read error");
        else { printf("Server receive: %s\n", msg); }
        close(client);  close(fd);  exit(0);
    }
    else{
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if(fd == -1) { perror("server socket error");  exit(1); }
        sleep(2);   // 等待服务器完成启动
#ifdef CLIENT_BIND
        struct sockaddr_in c_addr;
        c_addr.sin_family = AF_INET;
        c_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        c_addr.sin_port = htons(CLIENT_PORT);
        if(bind(fd, (struct sockaddr*)&c_addr, sizeof(c_addr)) < 0){
            perror("client bind error"); exit(1);
        }
#endif
        if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
            perror("connect error"); exit(1);
        }
        if(read(fd, msg, BSZ) < 0) perror("read error");
        else { printf("Client receive: %s\n", msg); }
        if(write(fd, "world", 5)!=5) perror("write error");
        waitpid(pid, NULL, 0);
    }
}

