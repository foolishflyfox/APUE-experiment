// exercise14-8.c
#include <stdio.h>
#include <ctype.h>
#include <aio.h>
#include <unistd.h>
#include <stdlib.h>

#define BSZ 10
char buf[BSZ+1];
off_t pos = 0;
struct aiocb cb;
unsigned char translate(unsigned char c){
    if(isalpha(c)){
        if(c >= 'n') c -= 13;
        else if(c >= 'a')  c += 13;
        else if(c >= 'N') c-= 13;
        else c += 13;
    }
    return c;
}
void foo(union sigval val){
    int n = aio_return(&cb);
    if(n == 0) exit(0);
    if(aio_error(&cb)) exit(1);
    buf[n] = '\0';
    for(int i=0; i<n; ++i) buf[i] = translate(buf[i]);
    printf("%s", buf);
    fflush(stdout);
    pos += n;
    cb.aio_offset = pos;
    if(aio_read(&cb)==-1){ perror("aio_read error"); exit(1); }
}
int main(){
    cb.aio_buf = buf;
    cb.aio_fildes = STDIN_FILENO;
    cb.aio_offset = 0;
    cb.aio_nbytes = BSZ;
    cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    cb.aio_sigevent.sigev_notify_function = foo;
    cb.aio_sigevent.sigev_notify_attributes = NULL;
    if(aio_read(&cb)==-1){ perror("aio_read error"); exit(1); }
    while(1) pause();
}
