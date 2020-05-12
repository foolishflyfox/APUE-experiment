// clock_gettime-demo.c
#include <time.h>
#include <stdio.h>

int main(){
    time_t t1 = time(NULL);
    if(t1==-1) perror("time error");
    else printf("         time: %lds\n", t1);
    struct timespec tsp;
    if(clock_gettime(CLOCK_REALTIME, &tsp)==-1){
        perror("clock_gettime error");
    }else{
        printf("clock_gettime: %lds %ldns\n", tsp.tv_sec, tsp.tv_nsec);
    }
}
