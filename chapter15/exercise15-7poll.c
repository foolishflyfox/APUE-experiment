// exercise15-7poll.c
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int fds[2];
    if(pipe(fds)==-1) { perror("pipe error"); exit(1); }
    pid_t pid = fork();
    if(pid < 0) { perror("fork error"); exit(1); }
    if(pid == 0){  // child
        close(fds[0]);
        sleep(1);
        close(fds[1]);  // 写者关闭管道
        printf("%ld: child exit\n", time(NULL));
    }else{
        printf("%ld: start\n", time(NULL));
        close(fds[1]);
        struct pollfd pfds[1];
        pfds[0].fd = fds[0];  pfds[0].events = POLLIN;
        int n = poll(pfds, 1, -1);
        if(n == -1) { fprintf(stderr, "%ld: poll error\n", time(NULL)); }
        else if(n == 0) { fprintf(stderr, "%ld: no read\n", time(NULL)); }
        else { printf("%ld: poll n = %d\n", time(NULL), n); }
    }
}
