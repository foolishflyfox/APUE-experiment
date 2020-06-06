// 14-3b.c
#include <stdio.h>
#include <fcntl.h>

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
    if(fd == -1){
        perror("open fail"); return 1;
    }
    if(fcntl(fd, F_SETLK, cfg_lock(&lk, F_WRLCK, 0, SEEK_SET, 4))==-1)
        perror("parent process lock 0~3 bytes error");
    // 再次加锁 0~3 字节
    int r = fcntl(fd, F_SETLK, cfg_lock(&lk, F_WRLCK, 0, SEEK_SET, 4));
    printf("relock %s\n", r==-1?"fail":"success");
}
