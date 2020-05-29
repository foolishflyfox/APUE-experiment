// printf-sleep.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("hello, world\n");
    sleep(10);
    _exit(0);
}
