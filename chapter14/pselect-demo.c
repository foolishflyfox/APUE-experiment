// pselect-demo.c
#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

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
        printf("%ld\"%s\":  %s\n", time(NULL), paths[fd==fd2], buf);
    }
    return 0;
}
int main(){
    fd1 = open(paths[0], O_RDONLY);  // 其他进程向管道写数据时,该语句才不被阻塞
    if(fd1==-1) { perror("open t1.pip error"); exit(1); }
    fd2 = open(paths[1], O_RDONLY);
    if(fd2==-1) { perror("open t2.pip error"); exit(1); }
    int maxfdp1 = fd1>fd2 ? (fd1+1) : (fd2+1);
    fd_set readfds;
    printf("wait for data...\n");
    // 记录是否到达文件尾
    int end1 = 0, end2 = 0;
    struct timespec ts;
    ts.tv_sec = 5; ts.tv_nsec = 0;  // ts 在 pselect 中不会被改变
    while(end1==0 || end2==0){
        FD_ZERO(&readfds); FD_SET(fd1, &readfds); FD_SET(fd2, &readfds);
        int n = pselect(maxfdp1, &readfds, NULL, NULL, &ts, NULL);
        if(n == -1){  // 出错，捕捉到一个信号
            continue;
        }else if(n == 0) {  // 指定时间内没有收到信号
            break;
        }else{  // 有准备好的描述符
            if(end1==0 && FD_ISSET(fd1, &readfds)) end1 = ReadData(fd1);
            if(end2==0 && FD_ISSET(fd2, &readfds)) end2 = ReadData(fd2);
        }
    }
}

