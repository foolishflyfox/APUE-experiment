// sigevent-signal.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <aio.h>
#include <string.h>

#define BSZ 10
char buf[BSZ+1];
struct aiocb cb;
void sig_usr1(int signo){
    printf("received SIGUSR1\n");
    printf("aio_error(&cb) = %d\n", aio_error(&cb));
    printf("aio_return(&cb) = %zd\n", aio_return(&cb));
    printf("read %zd chars: %s\n", strlen(buf), buf);
}
int main(){
    cb.aio_buf = buf;
    cb.aio_fildes = STDIN_FILENO;
    cb.aio_offset = 0;
    cb.aio_nbytes = BSZ;
    // 完成读取后，发送信号 SIGUSR1
    cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cb.aio_sigevent.sigev_signo = SIGUSR1;
    if(signal(SIGUSR1, sig_usr1) == SIG_ERR){
        perror("signal(SIGUSR1) error"); return 1;
    }
    if(aio_read(&cb) == -1){
        perror("aio_read error"); return 1;
    }
    printf("start pause\n");
    while(1) pause();
}
