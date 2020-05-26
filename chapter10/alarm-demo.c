// alarm-demo.c
#include <stdio.h>
#include <unistd.h>

int main(){
    alarm(3);
    for(int i=0; i<100; ++i){
        printf("%d\n", i); sleep(1);
    }
}
