// pipe-write.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#define BSZ 64
void sig_pipe(int signo){
    printf("received SIGPIPE\n");
}
int main(){
    int fd[2], n;
    if(pipe(fd) == -1) { perror("pipe error"); return 1; }
#ifdef DEAL_SIGPIPE
    if(signal(SIGPIPE, sig_pipe) == SIG_ERR){
        perror("signal(SIGPIPE) error"); return 1;
    }
#endif
    pid_t pid = fork();
    if(pid==-1) { perror("fork error"); return 1; }
    if(pid==0) {
        close(fd[1]);
        char buf[BSZ];
        if((n = read(fd[0], buf, BSZ)) > 0){
            buf[n] = '\0';
            printf("%d: %s\n", n, buf);
        }
        close(fd[0]);
    }else {
        close(fd[0]); sleep(1);
        if((n = write(fd[1], "abc", 3)) < 1)
            printf("n1 = %d, errno = %d\n", n, errno);
        sleep(1);
        if((n = write(fd[1], "xyz", 3)) < 1)
            printf("n2 = %d, errno = %d\n", n, errno);
        close(fd[1]);
    }
}

