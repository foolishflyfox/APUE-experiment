// fflush-demo.c
#include <stdio.h>
#include <unistd.h>

int main(){
    setvbuf(stdout, NULL, _IOFBF, 0);
    setvbuf(stderr, NULL, _IOFBF, 0);
    fprintf(stdout, " stdout ");
    fprintf(stderr, " stderr ");
    fflush(NULL);
    int fd = fileno(stdout);
    write(fd, " write ", 7);
}
