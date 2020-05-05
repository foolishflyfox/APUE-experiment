// cmp_fd_stream.c
#include <stdio.h>
#include <unistd.h>

int main(){
    fprintf(stdout, "hello,world");
    write(STDOUT_FILENO, "xxxx", 4);
    sleep(1);
    fprintf(stdout, "\n");
}

