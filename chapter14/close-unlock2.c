// close-unlock2.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static struct flock* cfg_lock(struct flock* lk, int type, off_t offset,
                        int whence, off_t len){
    lk->l_type = type;
    lk->l_whence = whence;
    lk->l_start = offset;
    lk->l_len = len;
    return lk;
}

int main(){
    struct flock lk;
    printf("parent pid = %d\n", getpid());
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error"); return 1;
    }
    int fd1 = open("tmp.txt", O_RDWR), fd2;
    if(fd1 == -1){
        perror("open error");  return 1;
    }
    if(pid){    // 父进程
        if((fd2 = open("tmp.txt", O_RDWR))==-1){
            perror("dup error"); return 1;
        }
        if(fcntl(fd1,F_SETLK,cfg_lock(&lk,F_WRLCK,0,SEEK_SET, 2))<0){
            perror("parent fcntl 1 error"); return 1;
        }
        sleep(2);
        close(fd2);         // 关闭 fd2，再在子进程中测试加锁情况
        sleep(2);
        if(write(fd1, "xx", 2)!=2) perror("write error");
    }else{      // 子进程
        sleep(1);
        if(fcntl(fd1,F_GETLK,cfg_lock(&lk,F_WRLCK,0,SEEK_SET,2))<0){
            perror("child fcntl 1 error"); return 1;
        }
        if(lk.l_type==F_UNLCK) printf("1: not lock\n");
        else printf("1: %d lock file\n", lk.l_pid);
        sleep(2);
        if(fcntl(fd1,F_GETLK,cfg_lock(&lk,F_WRLCK,0,SEEK_SET,2))<0){
            perror("child fcntl 2 error"); return 1;
        }
        if(lk.l_type==F_UNLCK) printf("2: not lock\n");
        else printf("2: %d lock file\n", lk.l_pid);
    }
}
