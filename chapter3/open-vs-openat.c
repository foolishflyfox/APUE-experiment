// open-vs-openat.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fds[10]; bzero(fds, sizeof(fds));
    fds[0] = open("t0", O_CREAT);
    fds[1] = openat(AT_FDCWD, "t1", O_CREAT);
    fds[2] = open("test", O_DIRECTORY);
    fds[3] = openat(fds[2], "t3", O_CREAT, S_IRUSR|S_IWUSR);
    for(int i=0; i<sizeof(fds)/sizeof(*fds) && fds[i]!=0; ++i){
        if(fds[i] > 0){
            close(fds[i]);
            printf("[t%d %d]  ", i, fds[i]);
        }else {
            printf("Can't create t%d\n", i);
        }
    }
}


