// write-pipe.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    int fd;
    if(pid==-1){
        perror("fork error"); return 1;
    }else if(pid!=0){
        if((fd = open("t1.pip", O_WRONLY))==-1){
            perror("open t1.pip error"); return 1;
        }
        sleep(1);
        write(fd, "hello1", 6);
        sleep(1); 
        write(fd, "world1", 6);
    }else{
        if((fd = open("t2.pip", O_WRONLY))==-1){
            perror("open t2.pip error"); return 1;
        }
        write(fd, "hello2", 6);
        sleep(1);
        write(fd, "world2", 6);
    }
}
