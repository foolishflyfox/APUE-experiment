// 8-31.c
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct tms tms;

// 耗时操作，n越大，系统cpu时间越多，用户cpu也会增加
void sys_cpu(int n){
    FILE* fp = tmpfile(); setbuf(fp, NULL);
    while(--n>0) fputc('a', fp);
}

static void pr_times(clock_t real, tms* tmsstart, tms* tmsend){
    static long clktck = 0;
    if(clktck == 0){
        if((clktck = sysconf(_SC_CLK_TCK)) < 0){
            perror("clktck error"); exit(1);
        }
    }
    printf("  real: %7.2f\n", real/(double)clktck);
    printf("  user: %7.2f\n", 
        (tmsend->tms_utime-tmsstart->tms_utime)/(double)clktck);
    printf("   sys: %7.2f\n",
        (tmsend->tms_stime-tmsstart->tms_stime)/(double)clktck);
    printf("child user: %7.2f\n",
        (tmsend->tms_cutime-tmsstart->tms_cutime)/(double)clktck);
    printf(" child sys: %7.2f\n",
        (tmsend->tms_cstime-tmsstart->tms_cstime)/(double)clktck);
}

static void do_cmd(char* cmd){
    tms tmsstart, tmsend;
    clock_t start, end;
    int status;
    printf("\ncommand: %s\n", cmd);
    if((start = times(&tmsstart))==-1){
        perror("first times error"); exit(1);
    }
    sys_cpu(1000000);
    if((status = system(cmd))==-1){
        perror("system error"); exit(1);
    }
    if((end = times(&tmsend))==-1){
        perror("second time error"); exit(1);
    }
    pr_times(end-start, &tmsstart, &tmsend);
}

int main(int argc, char* argv[]){
    setbuf(stdout, NULL);
    for(int i=1; i<argc; ++i)
        do_cmd(argv[i]);
}
