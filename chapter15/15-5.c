// 15-5.c
#include <stdio.h>
#include <unistd.h>
#define MAXLINE 1024
int main(){
    int n, fd[2];
    pid_t pid;
    char line[MAXLINE];
    if(pipe(fd) < 0) { perror("pipe error"); return 1; }
    if((pid = fork()) < 0) { perror("fork error"); return 1; }
    else if(pid > 0) {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    }else{
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
}

