// sigevent-thread.c
#include <stdio.h>
#include <unistd.h>
#include <aio.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

#define BSZ 10
char buf[BSZ+1];
struct aiocb cb;
void foo(union sigval val){
    printf("foo thread: %lu, val = %d\n", 
        (unsigned long)pthread_self(), val.sival_int);
    printf("aio_error(&cb) = %d\n", aio_error(&cb));
    printf("aio_return(&cb) = %zd\n", aio_return(&cb));
    printf("read %zd chars: %s\n", strlen(buf), buf);
}
int main(int argc, char *argv[]){
    cb.aio_buf = buf;
    cb.aio_fildes = argc>1?open(argv[1],O_RDONLY):STDIN_FILENO;
    if(cb.aio_fildes < 0){
        perror("open error"); return 1;
    }
    cb.aio_offset = 0;
    cb.aio_nbytes = BSZ;
    // 完成读取后，
    cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    // cb.aio_sigevent.sigev_signo = SIGUSR1;
    cb.aio_sigevent.sigev_notify_function = foo;
    cb.aio_sigevent.sigev_notify_attributes = NULL;
    cb.aio_sigevent.sigev_value.sival_int = 11;
    printf("main thread: %lu\n", (unsigned long)pthread_self());
    if(aio_read(&cb) == -1){
        perror("aio_read error"); return 1;
    }
    while(1) pause();
}
