// FILE_fd.c
#include <stdio.h>

int main(){
    printf("stdin fd = %d\n", fileno(stdin));
    printf("stdout fd = %d\n", fileno(stdout));
    printf("stderr fd = %d\n", fileno(stderr));
}

