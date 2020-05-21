// 8-30.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

unsigned long long count;
struct timeval end;

void checktime(char* str){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    if(tv.tv_sec > end.tv_sec || 
        (tv.tv_sec==end.tv_sec && tv.tv_usec>=end.tv_usec)){
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}

int main(int argc, char* argv[]){
    pid_t pid;
    char* s;
    int nzero, ret;
    int adj = 0;
    setbuf(stdout, NULL); // 标准输出设置无缓冲模式
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
    nzero = 0;
#endif
    printf("NZERO = %d\n", nzero);
    if(argc == 2)
        adj = strtol(argv[1], NULL, 10);
    gettimeofday(&end, NULL);
    end.tv_sec += 10;
    if(-1==(pid = fork())){
        perror("fork failed"); return 1;
    }else if(pid==0){
        s = "child";
        printf("current nice value in child is %d, adjusting by %d\n",
            nice(0)+nzero, adj);
        errno = 0;
        if((ret = nice(adj))==-1 && errno!=0){
            perror("child set scheduling priority"); return 1;
        }
        printf("now child nice value is %d\n", nice(0)+nzero);
    }else{
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0)+nzero);
    }
    for(;;){
        if(++count == 0){
            printf("%s counter wrap\n", s); return 0;
        }
        checktime(s);
    }
}
