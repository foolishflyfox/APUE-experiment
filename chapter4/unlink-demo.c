// unlink-demo.c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    if(open("tmp", O_RDWR) < 0)
        perror("open error");
    if(unlink("tmp")<0)
        perror("unlink error");
    else
        printf("file unlinked\n");
    sleep(15);
    printf("done\n");
}
