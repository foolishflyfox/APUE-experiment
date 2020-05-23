// macosx-fgcmd.c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){
    char buf[128];
    printf("EINTR = %d\n", EINTR);
    if(-1==read(STDIN_FILENO, buf, sizeof(buf))){
        fprintf(stderr, "errno = %d, ", errno);
        perror("read error");
    }
}