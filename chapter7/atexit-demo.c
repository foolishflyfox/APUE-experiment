// atexit-demo.c
#include <stdio.h>
#include <stdlib.h>

static void my_exit1(){ printf("first exit handler\n"); }
static void my_exit2(){ printf("second exit handler\n"); }

int main(){
    if(atexit(my_exit2)!=0) perror("can't register my_exit2");
    if(atexit(my_exit1)!=0) perror("can't register my_exit1");
    if(atexit(my_exit1)!=0) perror("can't register my_exit1");
    printf("main is done\n");
    return 0;
}

