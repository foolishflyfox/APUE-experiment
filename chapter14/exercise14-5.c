// exercise14-5.c
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/time.h>

void sleep_us(unsigned usecs){
    struct timeval tv = {usecs/1000000, usecs%1000000};
    select(5, NULL, NULL, NULL, &tv);
}
int main(){
    struct timeval t0, t1, t2;
    gettimeofday(&t0, NULL);
    sleep_us(666666);   // 等待 666666us
    gettimeofday(&t1, NULL);
    usleep(666666);     // 等待 666666us
    gettimeofday(&t2, NULL);
    printf("sleep_us sleep %ld us\n", 
            (t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec);
    printf("usleep sleep %ld us\n", 
            (t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec);
}
