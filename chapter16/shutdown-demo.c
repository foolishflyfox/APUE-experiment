// shutdown-demo.c
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

// 服务器端口为60000，如果被占用则更换为其他端口
int SERVER_PORT = 60000;
#define BSZ  511

// 服务器接收客户端发送的数据并显示
void* server_recv(void* pfd){
    int connfd = *(int*)pfd, cnt;
    char buf[BSZ+1];
    while((cnt = read(connfd, buf, BSZ)) > 0){
        buf[cnt] = '\0';
        printf("recv: %s\n", buf);
    }
    return NULL;
}
// 服务器进程函数
void* server(void* args){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) { perror("server socket error"); exit(1); }
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    while(bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr))==-1){
        servaddr.sin_port = htons(++SERVER_PORT);
    }
    if(listen(fd, 32)==-1){
        perror("server listen error"); exit(1);
    }
    printf("listen 0.0.0.0:%d success\n", SERVER_PORT);
    while(1){
        int connfd = accept(fd, NULL, 0);
        if(connfd==-1){ perror("accept error"); exit(1); }
        pthread_t pid;
        if(pthread_create(&pid, NULL, server_recv, &connfd)!=0){
            fprintf(stderr, "create read thread error\n"); exit(1);
        }
    }
    return NULL;
}
int getclient_fd(){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd==-1) { perror("socket error"); exit(1); }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    if(connect(fd, (struct sockaddr*)&addr, sizeof(addr))==-1){
        perror("connect error"); exit(1);
    }
    return fd;
}
void sigpipe(int signo){
    printf("get SIGPIPE\n");
}
int main(){
    if(signal(SIGPIPE, sigpipe) == SIG_ERR){
        perror("signal error"); exit(1);
    }
    pthread_t p1;
    if(pthread_create(&p1, NULL, server, NULL)!=0){
        fprintf(stderr, "create server thread error\n"); exit(1);
    }
    sleep(1);   // 让网络服务先启动
    int a1 = getclient_fd();
    int a2 = dup(a1);
    write(a1, "a1", 2); 
#ifdef SHUTDOWN
    shutdown(a1, SHUT_RDWR);
#else
    close(a1);
#endif
    sleep(2);
    write(a2, "a2", 2); 
    sleep(2);
}
