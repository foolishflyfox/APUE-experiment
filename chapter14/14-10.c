// 14-10.c
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
    int fd = open("tmp.txt", O_RDWR);
    struct flock lk;
    if(fd == -1){
        perror("open error"); exit(1);
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error"); exit(1);
    }
    if(pid > 0){  // parent
        if(lseek(fd, 0, SEEK_END)<0){
            perror("parent lseek error"); exit(1);
        }
        if(fcntl(fd,F_SETLKW,cfg_lock(&lk,F_WRLCK,0,SEEK_END,0))<0){
            perror("parent 1 fcntl error"); exit(1);
        }
        if(write(fd,"x",1)!=1){perror("parent 1 write error");exit(1);}
        if(fcntl(fd,F_SETLK,cfg_lock(&lk,F_UNLCK,0,SEEK_END,0))<0){
            perror("parent 2 fcntl error"); exit(1);
        }
        if(write(fd,"y",1)!=1){perror("parent 2 write error");exit(1);}
        if(waitpid(pid,NULL,0)<0){perror("waitpid error"); exit(1);}
    }else{  // child
        sleep(1);
        // 查看文件内容
        if(-1==system("cat ./tmp.txt")){
            perror("system error"); exit(1);
        }
        // 尝试对文件中倒数第二个字节(x)加锁
        if(fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,-2,SEEK_END,1))<0)
            perror("\nlock -2 byte error");
        else
            printf("\nlock -2 byte success\n");
        // 尝试对文件中倒数第一个字节(x)加锁
        if(fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,-1,SEEK_END,1))<0)
            perror("lock -1 byte error");
        else
            printf("lock -1 byte success\n");
    }
}
