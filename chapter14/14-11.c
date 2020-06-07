// 14-11.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
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
    int fd1 = open("tmp.txt", O_RDWR);              // 阻塞描述符
    int fd2 = open("tmp.txt", O_RDWR|O_NONBLOCK);   // 非阻塞描述符
    if(fd1==-1){ perror("open tmp.txt error"); exit(1);}
    struct flock lk;        char c;
    pid_t pids[8];
    // 对 0~3加读锁，对4~7加写锁
    if(fcntl(fd1,F_SETLK,cfg_lock(&lk,F_RDLCK,0,SEEK_SET,4))<0 ||
        fcntl(fd1,F_SETLK,cfg_lock(&lk,F_WRLCK,4,SEEK_SET,4))<0){
        perror("main fcntl error"); exit(1);
    }
    if((pids[0]=fork()) < 0){ perror("0 fork error"); exit(1); }
    if(pids[0]==0){
        if(read(fd1, &c, 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[1]=fork()) < 0){ perror("1 fork error"); exit(1); }
    if(pids[1]==0){
        if(write(fd1, "x", 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[2]=fork()) < 0){ perror("2 fork error"); exit(1); }
    if(pids[2]==0){
        if(read(fd2, &c, 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[3]=fork()) < 0){ perror("3 fork error"); exit(1); }
    if(pids[3]==0){
        if(write(fd2, "x", 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[4]=fork()) < 0){ perror("4 fork error"); exit(1); }
    if(pids[4]==0){
        if(lseek(fd1,4,SEEK_SET)==-1) {perror("4 lseek error");}
        if(read(fd1, &c, 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[5]=fork()) < 0){ perror("5 fork error"); exit(1); }
    if(pids[5]==0){
        if(lseek(fd1,5,SEEK_SET)==-1) {perror("5 lseek error");}
        if(write(fd1, "x", 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[6]=fork()) < 0){ perror("6 fork error"); exit(1); }
    if(pids[6]==0){
        if(lseek(fd2,6,SEEK_SET)==-1) {perror("6 lseek error");}
        if(read(fd2, &c, 1) != 1) exit(1);
        else exit(0);
    }
    if((pids[7]=fork()) < 0){ perror("7 fork error"); exit(1); }
    if(pids[7]==0){
        if(lseek(fd2,7,SEEK_SET)==-1) {perror("7 lseek error");}
        if(write(fd2, "x", 1) != 1) exit(1);
        else exit(0);
    }
    sleep(2);
    int x;
    for(int i=0; i<8; ++i){
        if(waitpid(pids[i], &x, WNOHANG)==0) printf("%9s", "blocks");
        else{
            if(WEXITSTATUS(x)==0) printf("%9s", "OK");
            else printf("%9s", "EAGAIN");
        }
        if(i==3 || i==7) printf("\n");
    }
}

