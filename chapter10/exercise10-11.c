// exercise10-11.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <signal.h>
#define BUFFSIZE 100

void sig_xfsz(int signo){
    fprintf(stderr, "received SIGXFSZ\n");
}

int main(void){
    int n, m;
    char buf[BUFFSIZE];
    if(SIG_ERR==signal(SIGXFSZ, sig_xfsz)){
        perror("signal(SIGXFSZ"); exit(1);
    }
    // 设置软资源
    struct rlimit rl;
    if(-1==getrlimit(RLIMIT_FSIZE, &rl)){
        perror("getrlimit error"); exit(1);
    }
    rl.rlim_cur = 1024;
    if(-1==setrlimit(RLIMIT_FSIZE, &rl)){
        perror("setrlimit error"); exit(1);
    }
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
        if ((m=write(STDOUT_FILENO, buf, n)) != n){
            fprintf(stderr, "write %d bytes, less than %d\n", m, n);
        }
    }
    if (n < 0){
        perror("read error"); exit(1);
    }
    exit(0);
}
