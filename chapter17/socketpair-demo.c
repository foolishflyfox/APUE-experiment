// socketpair-demo.c
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BSZ 512
void helper(const char* name, int fd){
    char buf[BSZ];
    sprintf(buf, "%s data", name);
    if((write(fd, buf, strlen(buf)))!=strlen(buf)){
        fprintf(stderr, "write %s error\n", buf); exit(1);
    }
    int n = read(fd, buf, BSZ);
    if(n < 0) { perror("read error"); exit(1); }
    buf[n] = '\0';
    printf("%s RECV: %s\n", name, buf);
}

int main(){
    int fds[2];
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0){
        perror("socketpair error"); exit(1);
    }
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    else if(pid == 0)  // child
        helper("child", fds[0]);
    else  // parent
        helper("parent", fds[1]);
}
