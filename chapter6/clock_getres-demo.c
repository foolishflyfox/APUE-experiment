// clock_getres-demo.c
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void show_accuracy(int type, int line){
    struct timespec tsp;
    const char* s = "\0";
    if(type==CLOCK_REALTIME) s = "CLOCK_REALTIME";
    else if(type==CLOCK_MONOTONIC) s = "CLOCK_MONOTONIC";
    else if(type==CLOCK_PROCESS_CPUTIME_ID) s = "CLOCK_PROCESS_CPUTIME_ID";
    else if(type==CLOCK_THREAD_CPUTIME_ID) s = "CLOCK_THREAD_CPUTIME_ID";
    if(clock_getres(type, &tsp)==-1)
        fprintf(stderr, "%d line error: %s\n", line, strerror(errno));
    else
        printf("%s accurate: %lds %ldns\n", s, tsp.tv_sec, tsp.tv_nsec);
}

int main(){
    show_accuracy(CLOCK_REALTIME, __LINE__);
    show_accuracy(CLOCK_MONOTONIC, __LINE__);
    show_accuracy(CLOCK_PROCESS_CPUTIME_ID, __LINE__);
    show_accuracy(CLOCK_THREAD_CPUTIME_ID, __LINE__);
}

