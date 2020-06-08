// poll-demo.c
#include <stdio.h>
#include <poll.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 511
int fd1, fd2;
const char* paths[2] = {"t1.pip", "t2.pip"};
int ReadData(int fd){
    static char buf[BUFSIZE+1];
    int n = read(fd, buf, BUFSIZE);
    if(n <= 0){
        if(n < 0) perror("read error");
        return 1;
    }else{
        buf[n] = '\0';
        printf("%ld'%s':  %s\n", time(NULL), paths[fd==fd2], buf);
    }
    return 0;
}
int main(){
    fd1 = open(paths[0], O_RDONLY);  // 其他进程向管道写数据时,该语句才不被阻塞
    if(fd1==-1) { perror("open t1.pip error"); exit(1); }
    fd2 = open(paths[1], O_RDONLY);
    if(fd2==-1) { perror("open t2.pip error"); exit(1); }
    struct pollfd pfds[2];
    pfds[0].fd = fd1;  pfds[0].events = POLLIN;
    pfds[1].fd = fd2;  pfds[1].events = POLLIN;
    for( ; ;){
        printf("xxx\n");
        int res = poll(pfds, 2, 5000);// 时间以毫秒为单位
        printf("yyy\n");
        if(res == -1){  // 出错，捕捉到一个信号
            break;
        }else  if(res == 0){  // 指定时间内没有收到信号
            break;
        }else{
            if(pfds[0].revents & POLLIN) ReadData(pfds[0].fd);
            if(pfds[1].revents & POLLIN) ReadData(pfds[1].fd);
        }
    }
}
