// clock_nanosleep-demo.c
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

// 耗时操作，n越大，系统cpu时间越多，用户cpu也会增加
void sys_cpu(int n){
    FILE* fp = tmpfile(); setbuf(fp, NULL);
    while(--n>0) fputc('a', fp);
}
void sig_deal(int signo){
    printf("running sig_deal\n");
}
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]); return 1;
    }
    struct timespec reqtp, remtp;
    reqtp.tv_sec = atoi(argv[1]);
    reqtp.tv_nsec = 500000000;
    if(SIG_ERR==signal(SIGQUIT, sig_deal)){
        perror("signal error"); return 1;
    }
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &reqtp, &remtp);
}
