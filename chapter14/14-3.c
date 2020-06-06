// 14-3.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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
        perror("open fail"); exit(1);
    }
    pid_t pid = fork();
    if(pid){    // 父进程
        // 0~1 字节不加锁
        // 2~3 字节加读锁
        if(fcntl(fd, F_SETLK, cfg_lock(&lk, F_RDLCK, 2, SEEK_SET, 2))==-1)
            perror("parent process lock 2~3 byte error");
        // 4~5 字节加写锁
        if(fcntl(fd, F_SETLK, cfg_lock(&lk, F_WRLCK, 4, SEEK_SET, 2))==-1)
            perror("parent process lock 4~5 byte error");
        if(waitpid(pid, NULL, 0)<0)
            perror("parent process waitpid error");
    }else{      // 子进程
        sleep(1);
        int rs[6];
        const char* ss[2] = {"OK", "denied"};
        // 尝试给第0、1字节分别加读锁和写锁
        rs[0] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,0,SEEK_SET,1));
        rs[1] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_WRLCK,1,SEEK_SET,1));
        // 尝试给第2、3字节分别加读锁和写锁
        rs[2] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,2,SEEK_SET,1));
        rs[3] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_WRLCK,3,SEEK_SET,1));
        // 尝试给第4、5字节分别加读锁和写锁
        rs[4] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,4,SEEK_SET,1));
        rs[5] = fcntl(fd,F_SETLK,cfg_lock(&lk,F_WRLCK,5,SEEK_SET,1));
        for(int i=0; i<6; i+=2){
            printf("%d: %10s %10s\n", i/2+1, ss[rs[i]==-1], ss[rs[i+1]==-1]);
        }
    }
}

