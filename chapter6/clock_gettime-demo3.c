// clock_gettime-demo3.c
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

int fabonacci(int n){
    if(n<=0) return 0;
    if(n<=2) return 1;
    return fabonacci(n-1)+fabonacci(n-2);
}
int main(){
    fabonacci(45);
    int fd = open("tmp", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if(fd==-1) {perror("open error"); return 1;}
    for(int i=0; i<1000000; ++i) write(fd, "x", 1);
    sleep(2);
    struct timespec tsp;
    if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tsp)==-1){
        perror("clock_gettime error");
    }else{
        printf("process cpu time: %lds %ldns\n", tsp.tv_sec, tsp.tv_nsec);
    }
}
