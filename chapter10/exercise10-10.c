// exercise10-10.c
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
    struct timeval tv;
    for(int i=1; 1; ++i){
        int t = 60;
        while((t = sleep(t)) > 0){
            sleep(t);
        }
        if(i==5){
            gettimeofday(&tv, NULL);
            printf("%ld\n", tv.tv_sec);
            i = 0;
        }
    }
}
