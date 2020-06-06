// 14-3c.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef SET_TYPE
#define SET_TYPE F_SETLK
#endif

struct flock* cfg_lock(struct flock* lk, int type, off_t offset,
                        int whence, off_t len){
    lk->l_type = type;
    lk->l_whence = whence;
    lk->l_start = offset;
    lk->l_len = len;
    return lk;
}
int main(){
    struct flock lk;
    int fd = open("tmp.txt", O_RDWR);
    if(fd == -1){   perror("open fail"); return 1;  }
    if(fcntl(fd, SET_TYPE, cfg_lock(&lk, F_WRLCK, 0, SEEK_SET, 4))==-1){
        perror("parent process lock 0~3 bytes error");
        return 1;
    }
    sleep(5);  printf("end of main\n");
}
