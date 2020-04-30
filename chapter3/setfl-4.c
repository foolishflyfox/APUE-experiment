// setfl-4.c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fd = atoi(argv[1]);
    char c;
    read(fd, &c, 1);
    printf("read '%c' from df %d\n", c, fd);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL)|O_APPEND);
    write(fd, "b\n", 2);
}

