// exercise8-7.c
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    DIR* pdir = opendir("/");
    if(NULL==pdir){ perror("opendir error"); return 1; }
    int flag = fcntl(dirfd(pdir), F_GETFD);
    if(-1==flag){ perror("1 fcntl error"); return 1; }
    printf("opendir '/', FD_CLOEXEC=%s\n", (flag&FD_CLOEXEC)?"True":"False");

    int fd = open("/", O_RDONLY|O_DIRECTORY);
    if(-1==fd){ perror("open error"); return 1; }
    flag = fcntl(fd, F_GETFD);
    if(-1==flag) { perror("2 fcntl error"); return 1;}
    printf("open '/', FD_CLOEXEC=%s\n", (flag&FD_CLOEXEC)?"True":"False");
}
