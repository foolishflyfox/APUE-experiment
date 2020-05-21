// 8-25.c
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("real uid = %u, effective uid = %u\n", getuid(), geteuid());
    return 0;
}

