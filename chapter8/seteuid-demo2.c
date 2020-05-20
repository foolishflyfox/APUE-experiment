// seteuid-demo2.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

void writetmp(){
    int fd;
    if(-1==(fd=open("tmp", O_WRONLY))){
        printf("%u(%s) can't write tmp : %s\n", geteuid(), 
            getpwuid(geteuid())->pw_name, strerror(errno));
    }else{
        printf("%u(%s) can write tmp : %s\n", geteuid(), 
            getpwuid(geteuid())->pw_name, strerror(errno));
        close(fd);
    }
}

int main(){
    uid_t uid = getuid(), euid = geteuid();
    int fd;
    writetmp();
    if(seteuid(uid)==-1){
        perror("seteuid error"); return 1;
    }else
        writetmp();
}

