// 14-7.c
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

static struct flock* cfg_lock(struct flock* lk, int type, off_t offset,
                        int whence, off_t len){
    lk->l_type = type;
    lk->l_whence = whence;
    lk->l_start = offset;
    lk->l_len = len;
    return lk;
}
static void lockabyte(const char* name, int fd, off_t offset){
    struct flock lk;
    if(fcntl(fd, F_SETLKW, cfg_lock(&lk,F_WRLCK,offset,SEEK_SET,1))<0){
        fprintf(stderr, "%s fcntl error: %s\n", name, strerror(errno));
        exit(1);
    }
    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

static int g_wait;
static void sig_usr1(int signo){ g_wait = 0; }
static void TELL_WAIT(){
    g_wait = 1;
    signal(SIGUSR1, sig_usr1);
}
void WAIT_CHILD(){ while(g_wait) pause(); }
void TELL_CHILD(pid_t pid){ kill(pid, SIGUSR1); }
void WAIT_PARENT(){ while(g_wait) pause(); }
void TELL_PARENT(pid_t pid){ kill(pid, SIGUSR1); }

int main(void){
    /* Create a file and write two bytes to it */
    int fd = creat("templock", 0644);
    if(fd < 0){
        perror("creat error"); exit(1);
    }
    if(write(fd, "ab", 2) != 2){
        perror("write error"); exit(1);
    }
    TELL_WAIT();
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error"); exit(1);
    }else if(pid == 0){             /* child */
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    }else{                          /* parent */
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
}


