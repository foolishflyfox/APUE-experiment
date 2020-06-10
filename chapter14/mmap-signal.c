// mmap-signal.h
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env;
void sig_segv(int signo){printf("received SIGSEGV\n"); siglongjmp(env,1);}
void sig_bus(int signo){printf("received SIGBUS\n"); siglongjmp(env,1);}

int main(){
    if(SIG_ERR == signal(SIGSEGV, sig_segv)) {
        perror("signal(SIGSEGV) error"); return 1;
    }
    if(SIG_ERR == signal(SIGBUS, sig_bus)) {
        perror("signal(SIGBUS) error"); return 1;
    }
    int fd1 = open("tmp.txt", O_RDWR);
    if(fd1==-1) { perror("1 open error\n"); return 1; }
    char* buf = mmap(NULL, 128, PROT_READ, MAP_PRIVATE, fd1, 0);
    if(sigsetjmp(env, 1)==0)  // 不加这一条会不断进入信号处理函数
        buf[0] = 'x';   // 写出错，会产生信号

    // sleep(1);
    if(open("tmp.txt", O_TRUNC|O_WRONLY)==-1){
        perror("2 open error\n"); return 1;
    }
    if(sigsetjmp(env, 1)==0) printf("%c\n",buf[1]);
}
