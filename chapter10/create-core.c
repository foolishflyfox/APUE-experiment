// create-core.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("pid = %d\n", getpid());
    abort();
    printf("main exit\n");
}
