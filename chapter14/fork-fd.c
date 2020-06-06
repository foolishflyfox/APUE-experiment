// fork-fd.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("tmp.txt", O_RDWR);
    if(fd == -1){
        perror("open error"); return 1;
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error"); return 1;
    }
    if(pid){
        if(write(fd, "xxxx", 4) != 4){
            perror("parent write error"); return 1;
        }
        sleep(2);
    }else{
        sleep(1);
        if(write(fd, "yy", 2) != 2){
            perror("child write error"); return 1;
        }
    }
}
