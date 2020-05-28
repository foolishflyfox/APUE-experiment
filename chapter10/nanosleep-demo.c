// nanosleep-demo.c
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

void current_time(){
    struct timespec tsp;
    if(clock_gettime(CLOCK_REALTIME, &tsp)==-1){
        perror("clock_gettime error");
    }else{
        printf("%ld.%09ldns\n", tsp.tv_sec, tsp.tv_nsec);
    }
}

int main(){
    struct timespec req, rem;
    req.tv_sec = 5;
    req.tv_nsec = 678912345;
    current_time();
    nanosleep(&req, &rem);
    current_time();
    printf("req: %ld.%09ld\n", req.tv_sec, req.tv_nsec);
    printf("rem: %ld.%09ld\n", rem.tv_sec, rem.tv_nsec);
}
