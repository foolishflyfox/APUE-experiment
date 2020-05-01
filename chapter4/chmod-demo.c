// chmod-demo.c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
    struct stat statbuf;
    // 开启foo的set-group-ID，关闭group-execute
    // foo的其他模式不变，因此需要先获取原模式
    if(stat("foo", &statbuf)<0)
        perror("state error for foo");
    if(chmod("foo", (statbuf.st_mode|S_ISGID)&(~S_IXGRP))<0)
        perror("chmod error for foo");
    // 设置bar模式为 rw-r--r--
    if(chmod("bar", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
        perror("chmod error for bar");
}

