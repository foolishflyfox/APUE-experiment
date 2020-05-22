// tcgetpgrp-demo.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    pid_t pgrp = -1;
    int fd = open("/dev/tty", O_RDONLY);
    while(1){
        pid_t t = tcgetpgrp(fd);
        if(t!=pgrp){
            printf("%s: %d is foreground process\n", argv[0], t);
            pgrp = t;
        }
        sleep(1);
    }
}

