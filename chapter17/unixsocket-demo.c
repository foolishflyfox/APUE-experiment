// unixsocket-demo.c
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BSZ 127
int serv_listen(const char* name);
int serv_accept(int listenfd, uid_t *uidptr);
int cli_conn(const char* name);

int main(){
    const char* name = "hello";
    pid_t pid = fork();
    if(pid == -1) { perror("fork error"); exit(1); }
    if(pid == 0){
        int servfd = serv_listen(name);
        if(servfd < 0){
            perror("serv_listen error"); exit(1);
        }
        uid_t uid;
        int clifd = serv_accept(servfd, &uid);
        if(clifd < 0) {
            perror("serv_accept error"); exit(1);
        }
        char data[BSZ+1] = "server data";
        if(write(clifd, data, strlen(data)) != strlen(data)){
            perror("server write error"); exit(1);
        }
        int n = read(clifd, data, BSZ);
        if(n<0) { perror("server read error"); exit(1); }
        data[n] = '\0';
        printf("Server receive: %s\n", data);
    }else{
        sleep(1);  // 等待服务器启动完成
        int clifd = cli_conn(name);
        if(clifd < 0) {
            perror("cli_conn error"); exit(1);
        }
        char data[BSZ+1] = "client data";
        if(write(clifd, data, strlen(data)) != strlen(data)){
            perror("client write error"); exit(1);
        }
        int n = read(clifd, data, BSZ);
        if(n<0) { perror("client read error"); exit(1); }
        data[n] = '\0';
        printf("Client receive: %s\n", data);
    }
}
