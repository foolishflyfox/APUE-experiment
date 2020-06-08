// processes-demo.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 511
int main(){
    int n;
    char buf[BUFSIZE+1];
    pid_t pid = fork();
    if(pid==-1){
        perror("fork error"); return 1;
    }else if(pid){  // parent
        int fd1 = open("t1.pip", O_RDONLY|O_NONBLOCK);
        if(fd1==-1) {perror("open t1.pip error"); return 1;}
        for( ; ;) {
            if((n = read(fd1, buf, BUFSIZ))>0){
                buf[n] = '\0';
                printf("{t1.pip}:  %s\n", buf);
            }
        }
    }else{  // child
        int fd2 = open("t2.pip", O_RDONLY|O_NONBLOCK);
        if(fd2==-1) {perror("open t2.pip error"); return 1;}
        for( ; ;) {
            if((n = read(fd2, buf, BUFSIZ))>0){
                buf[n] = '\0';
                printf("{t2.pip}:  %s\n", buf);
            }
        }
    }
}
