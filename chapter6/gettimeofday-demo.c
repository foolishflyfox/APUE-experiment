// gettimeofday-demo.c
#include <sys/time.h>
#include <stdio.h>
#include <time.h>

int main(){
    struct timeval tv;
    struct timezone tz;
    printf("time: %ld\n", time(NULL));
    if(gettimeofday(&tv, NULL)==-1){
        perror("first gettimeofday error");
    }else{
        printf("%ld s, %ld us\n", tv.tv_sec, (long)tv.tv_usec);
    }
}
