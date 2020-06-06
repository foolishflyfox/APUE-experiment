// f_getlk-demo.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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
    // 测试 2、3、4 字节是否锁住
    if(-1==fcntl(fd, F_GETLK, cfg_lock(&lk, F_RDLCK, 2, SEEK_SET, 3))){
        perror("fcntl(F_GETLK) error"); return 1;
    }
    if(lk.l_type == F_UNLCK){
        printf("not lock\n");
        // 若未加锁，则将这3个字节加读锁
        lk.l_type = F_RDLCK;
        if(fcntl(fd, F_SETLK, &lk)==-1){
            perror("fcntl(F_SETLK) error"); return 1;
        }
        sleep(5);
    }else{
        printf("lock: pid=%d, type=%s lock, start=%ld, len=%ld\n", 
            lk.l_pid, lk.l_type==F_RDLCK?"read":"write", 
            (long)lk.l_start, (long)lk.l_len);
    }
}
