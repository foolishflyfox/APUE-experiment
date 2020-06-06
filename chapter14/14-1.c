// 14-1.c
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// set_fl 来自 Figure 3.12
void set_fl(int fd, int flags){/* flags are files status flags to turn on */
    int val;
    if((val = fcntl(fd, F_GETFL)) < 0){
        perror("set_fl fcntl(F_GETFL) error"); exit(1);
    }
    val |= flags;
    if(fcntl(fd, F_SETFL, val)){
        perror("set_fl fcntl(F_SETFL) error"); exit(1);
    }
}
void clr_fl(int fd, int flags){
    int val;
    if((val = fcntl(fd, F_GETFL)) < 0){
        perror("clr_fl fcntl(F_GETFL) error"); exit(1);
    }
    val &= ~flags;
    if(fcntl(fd, F_SETFL, val) < 0){
        perror("clr_fl fcntl(F_SETFL) error"); exit(1);
    }
}

char buf[500000];

int main(){
    int ntowrite, nwrite;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK);  /* set nonblocking */

    ptr = buf;
    while(ntowrite > 0){
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
        if(nwrite > 0){
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
    clr_fl(STDOUT_FILENO, O_NONBLOCK);  /* clear nonblocking */
}

