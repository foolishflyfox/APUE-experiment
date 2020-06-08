// bsd-async.c
// 验证 APUE 14.5.2 节(Mac OS X下没通过，错误为
//  Operation not supported on socke，发生在执行 fcntl 时)
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define BUFSIZE 511
int fd1, fd2;
char buf1[BUFSIZE+1], buf2[BUFSIZE+1];
void sig_io(int signo){
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
    if(signal(SIGIO, sig_io)==SIG_ERR){
        perror("signal error"); return 1;
    }
    if(fcntl(fd2, F_SETOWN, getpid())==-1){
        perror("fcntl(F_SETOWN) error"); exit(1);
    }
    // if(fcntl(fd2, F_SETFL, ))
    int n;
    while((n = read(fd1, buf1, BUFSIZ)) > 0) {
        buf1[n] = '\0';
        printf("t1.pip:  %s\n", buf1);
    }
}

