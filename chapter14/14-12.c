// 14-12.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
struct flock* cfg_lock(struct flock* lk, int type, off_t offset,
                        int whence, off_t len){
    lk->l_type = type;
    lk->l_whence = whence;
    lk->l_start = offset;
    lk->l_len = len;
    return lk;
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

int main(int argc, char *argv[]){
    int             fd;
    pid_t           pid;
    char            buf[5];
    struct stat     statbuf;
    struct flock    lk;
    if(argc != 2){
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if((fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0644))<0){
        perror("open error"); exit(1);
    }
    if(write(fd, "abcdef", 6)!=6){
        perror("write error"); exit(1);
    }
    /* turn on set-group-ID and turn off group-execute */
    if(fstat(fd, &statbuf) < 0){
        perror("fstat error"); exit(1);
    }
    if(fchmod(fd, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0){
        perror("fchmod error"); exit(1);
    }
    TELL_WAIT();
    if((pid = fork()) < 0) {
        perror("fork error"); exit(1);
    }else if(pid>0){  // parent
        /* write lock entire file */
        if(fcntl(fd,F_SETLK,cfg_lock(&lk,F_WRLCK,0,SEEK_SET,0))<0){
            perror("write lock error"); exit(1);
        }
        TELL_CHILD(pid);
        if(waitpid(pid, NULL, 0) < 0){
            perror("waitpid error"); exit(1);
        }
    }else{  // child
        WAIT_PARENT();  /* wait for parent to set lock */
        int flags = fcntl(fd, F_GETFL, 0);
        if(flags < 0){
            perror("fcntl(F_GETFL) error"); exit(1);
        }
        flags |= O_NONBLOCK;
        if(fcntl(fd, F_SETFL, flags) < 0){
            perror("fcntl(F_SETFL) error"); exit(1);
        }
        /* first let's see what error we get if region is locked */
        if(fcntl(fd,F_SETLK,cfg_lock(&lk,F_RDLCK,0,SEEK_SET,0))!=-1){
            printf("child: read_lock succeeded\n"); exit(0);
        }
        printf("read_lock of alread-locked region returns %d\n", errno);
        /* now try to read the mandatory locked file */
        if(lseek(fd, 0, SEEK_SET)==-1){
            perror("lseek error"); exit(1);
        }
        if (read(fd, buf, 2) < 0){
            perror("read failed (mandatory locking works)"); exit(1);
        }else{
            printf("read OK (no mandatory locking), buf = %2.2s\n", buf);
        }
    }
}
