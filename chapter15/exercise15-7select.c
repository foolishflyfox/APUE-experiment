// exercise15-7select.c
#include <stdio.h>
#include <sys/select.h>
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
        fd_set readfds;
        FD_ZERO(&readfds); FD_SET(fds[0], &readfds);
        int maxfdp1 = fds[0]+1;
        int n = select(maxfdp1, &readfds, NULL, NULL, NULL);
        if(n==-1) fprintf(stderr, "%ld: select error\n", time(NULL));
        else if(n == 0) fprintf(stderr, "%ld: no read\n", time(NULL));
        else{
            printf("%ld: n = %d\n", time(NULL), n);
            if(FD_ISSET(fds[0], &readfds)) printf("readable\n");
        }
    }
}

