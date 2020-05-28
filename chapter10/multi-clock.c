// multi-clock.c
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>

#define MAX_CLOCKS 1024
typedef void SigFunc(int);
typedef struct {
    int tm;
    SigFunc* func;
}TimeAction;

static TimeAction clock_buf[MAX_CLOCKS];
static int clock_cnt = 0;

void deal_alarm(int signo){
    time_t cur_tm = time(NULL);
    int p1=0, p2=0, min_tm = INT_MAX;
    for(; p2<clock_cnt; ++p2){
        if(cur_tm >= clock_buf[p2].tm){
            clock_buf[p2].func(SIGALRM);
        }else{
            min_tm = min_tm<clock_buf[p2].tm?min_tm:clock_buf[p2].tm;
            if(p1!=p2){
                clock_buf[p1].tm = clock_buf[p2].tm;
                clock_buf[p1].func = clock_buf[p2].func;
            }
            ++p1;
        }
    }
    clock_cnt -= p2-p1;
    if(clock_cnt > 0){
        alarm(min_tm - time(NULL));
    }
}

static void init_clock(){
    if(SIG_ERR == signal(SIGALRM, deal_alarm)){
        perror("signal(SIGALRM) error"); _exit(1);
    }
}
static void add_clock(int t, SigFunc* func){
    time_t cur_tm = time(NULL);
    time_t alarm_tm = cur_tm + t;
    clock_buf[clock_cnt].tm = alarm_tm;
    clock_buf[clock_cnt].func = func;
    for(int i=0; i < clock_cnt; ++i){
        if(alarm_tm >= clock_buf[i].tm){
            clock_cnt += 1;
            return;
        }
    }
    clock_cnt += 1;
    alarm(t);
}

static void foo(int signo){ printf("%ld: foo\n", time(NULL)); }
static void bar(int signo){ printf("%ld: bar\n", time(NULL)); }

int main(){
    init_clock();
    add_clock(2, foo);
    add_clock(5, bar);
    add_clock(6, foo);
    for(; ;) pause();
}

