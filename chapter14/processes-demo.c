// processes-demo.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#define BUFSIZE 511
int main(){
    int n;
    char buf[BUFSIZE+1];
    pid_t pid = fork();
    if(pid==-1){
        perror("fork error"); return 1;
    }else if(pid){  // parent
        int fd1 = open("t1.pip", O_RDONLY);
        if(fd1==-1) { perror("open t1.pip error"); return 1; }
        while((n = read(fd1, buf, BUFSIZ))>0){
            buf[n] = '\0';
            printf("%ld{t1.pip}:  %s\n", time(NULL), buf);
        }
        if(waitpid(pid, NULL, 0)!=pid) perror("wait error");
    }else{  // child
        int fd2 = open("t2.pip", O_RDONLY);
        if(fd2==-1) { perror("open t2.pip error"); return 1; }
        while((n = read(fd2, buf, BUFSIZ))>0){
            buf[n] = '\0';
            printf("%ld{t2.pip}:  %s\n", time(NULL), buf);
        }
    }
}
