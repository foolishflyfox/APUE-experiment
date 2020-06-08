// ioctl-demo.c
// 验证 APUE 14.5.1 节(ubuntu1804下没通过，错误为
// Inappropriate ioctl for device，发生在执行 ioctl 时)
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stropts.h>

#define BUFSIZE 511
int fd1, fd2;
char buf1[BUFSIZE+1], buf2[BUFSIZE+1];
void sig_poll(int signo){
    int n = read(fd2, buf2, BUFSIZ);
    if(n > 0){
        buf2[n] = '\0';
        printf("t2.pip:  %s\n", buf2);
    }
}
int main(){
    fd1 = open("t1.pip", O_RDONLY);  // 其他进程向管道写数据时,该语句才不被阻塞
    if(fd1==-1) { perror("open t1.pip error"); exit(1); }
    fd2 = open("t2.pip", O_RDONLY);
    if(fd2==-1) { perror("open t2.pip error"); exit(1); }
    if(signal(SIGPOLL, sig_poll)==SIG_ERR){
        perror("signal error"); return 1;
    }
    if(ioctl(fd2, I_SETSIG, S_INPUT)==-1){
        perror("ioctl error"); return 1;
    }
    int n;
    while((n = read(fd1, buf1, BUFSIZ)) > 0) {
        buf1[n] = '\0';
        printf("t1.pip:  %s\n", buf1);
    }
}

