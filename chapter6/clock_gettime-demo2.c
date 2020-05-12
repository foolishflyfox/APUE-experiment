// clock_gettime-demo2.c
#include <time.h>
#include <stdio.h>

int main(){
    struct timespec tsp;
    if(clock_gettime(CLOCK_MONOTONIC, &tsp)==-1){
        perror("clock_gettime error");
    }else{
        printf("monotonic: %lds %ldns, ", tsp.tv_sec, tsp.tv_nsec);
        int days = tsp.tv_sec/(3600*24), seconds = tsp.tv_sec%(3600*24);
        int hours = seconds/3600;
        seconds = seconds%3600;
        int minutes = seconds/60;
        seconds = seconds%60;
        printf("up %d days, %d:%d:%d\n", days, hours, minutes, seconds);
    }
}
