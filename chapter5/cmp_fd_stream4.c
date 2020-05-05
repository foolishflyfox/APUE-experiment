// cmp_fd_stream4.c
#include <stdio.h>
#include <unistd.h>

int main(){
    fprintf(stderr, "hello,world");
    write(STDOUT_FILENO, "xxxx", 4);
    sleep(1);
    fprintf(stdout, "\n");
}

