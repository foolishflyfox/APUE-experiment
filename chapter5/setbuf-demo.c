// setbuf-demo.c
#include <stdio.h>
#include <unistd.h>

int main(){
    setbuf(stdout, NULL);
    fprintf(stdout, "hello,world");
    write(STDOUT_FILENO, "xxxx", 4);
    sleep(1);
    fprintf(stdout, "\n");
}

