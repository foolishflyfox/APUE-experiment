// exercise10-11.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFSIZE 100

int main(void){
    int n;
    char buf[BUFFSIZE];
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n){
            perror("write error"); exit(1);
        }
    if (n < 0){
        perror("read error"); exit(1);
    }
    exit(0);
}
