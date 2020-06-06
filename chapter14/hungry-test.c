// hungry-test.c
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
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
    pid_t pid;
    for(int i=0; i<6; ++i){
        if((pid = fork())==-1){
            fprintf(stderr, "fork process %d error\n", i); return 1;
        }
        if(pid == 0){   // child process
            int fd = open("tmp.txt", O_RDWR);
            if(fd==-1){
                fprintf(stderr, "child %d open error", i); return 1;
            }
            sleep(i);
            if(fcntl(fd, F_SETLKW, cfg_lock(&lk,F_RDLCK,0,SEEK_SET,1))<0){
                fprintf(stderr, "child %d fcntl error", i); return 1;
            }
            printf("%ld: child %d get read lock\n", time(NULL), i);
            sleep(2);
            return 0;
        }
    }
    sleep(3);
    int fd = open("tmp.txt", O_RDWR);
    if(fd==-1){
        fprintf(stderr, "parent open error"); return 1;
    }
    printf("%ld: parent request write lock\n", time(NULL));
    if(fcntl(fd, F_SETLKW, cfg_lock(&lk,F_WRLCK,0,SEEK_SET,1))<0){
        fprintf(stderr, "parent fcntl error"); return 1;
    }
    printf("%ld: parent get write lock\n", time(NULL));
    sleep(6);
}

