// pipe-read.c
#include <stdio.h>
#include <unistd.h>

#define BSZ 5
int main(){
    int fd[2];
    if(pipe(fd) == -1) { perror("pipe error"); return 1; }
    pid_t pid = fork();
    if(pid==-1) { perror("fork error"); return 1; }
    if(pid) {
        close(fd[1]);
        char buf[BSZ];
        int n;
        while((n = read(fd[0], buf, BSZ)) > 0){
            buf[n] = '\0';
            printf("%d: %s\n", n, buf);
        }
        printf("n = %d\n", n);
    }else {
        close(fd[0]);
        write(fd[1], "abc", 3); sleep(1);
        write(fd[1], "uuvvwwxxyyzz", 12); sleep(1);
        close(fd[1]);
    }
}

