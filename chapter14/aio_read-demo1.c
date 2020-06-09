// aio_read-demo1.c
#include <stdio.h>
#include <aio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define BUFSIZE 511
typedef void(*SigFunc)(int);
const char* paths[] = {"t1.pip", "t2.pip"};
char buf1[BUFSIZE+1], buf2[BUFSIZE+1];
struct aiocb cb1, cb2;
void sig_usr1(int signo){
    int n = aio_return(&cb1);
    if(n < 1) return;
    buf1[n] = '\0';
    printf("%ld!%s!:  %s\n", time(NULL), paths[0], buf1);
    if(aio_read(&cb1)==-1){ perror("aio(&cb1) error"); exit(1); }
}
void sig_usr2(int signo){
    int n = aio_return(&cb2);
    if(n < 1) return ;
    buf2[n] = '\0';
    printf("%ld!%s!:  %s\n", time(NULL), paths[1], buf2);
    if(aio_read(&cb2)==-1){ perror("aio(&cb2) error"); exit(1); }
}

void init_aiocb(struct aiocb* cbptr, int ipath, char* buf){
    cbptr->aio_buf = buf;
    if((cbptr->aio_fildes = open(paths[ipath], O_RDONLY)) < 0){
        fprintf(stderr, "open %s error\n", paths[ipath]); exit(1);
    }
    cbptr->aio_nbytes = BUFSIZE;
    cbptr->aio_offset = 0;
    cbptr->aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    cbptr->aio_sigevent.sigev_signo = (ipath?SIGUSR2:SIGUSR1);
    if(signal(cbptr->aio_sigevent.sigev_signo, 
                (ipath?sig_usr2:sig_usr1)) == SIG_ERR){
        perror("signal error"); exit(1);
    }
}

int main(){
    setbuf(stdout, NULL);
    init_aiocb(&cb1, 0, buf1);
    init_aiocb(&cb2, 1, buf2);
    if(aio_read(&cb1)==-1){ perror("aio(&cb1) error"); exit(1); }
    if(aio_read(&cb2)==-1){ perror("aio(&cb2) error"); exit(1); }
    while (1) pause();
}
