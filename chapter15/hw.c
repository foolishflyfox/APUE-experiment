// hw.c
#include <stdio.h>
#include <unistd.h>
int main(){
    fprintf(stderr, "%d: hello,world\n", getpid());
}

