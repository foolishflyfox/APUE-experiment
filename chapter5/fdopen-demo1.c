// fdopen-demo1.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("tmp", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd==-1){
        perror("open tmp error"); return 1;
    }
    if(write(fd, "xxxxxx", 6)==-1){
        perror("write error"); return 1;
    }
    FILE* fp = fdopen(fd, "w");
    if(fp==NULL){
        perror("fdopen error"); return 1;
    }
    if(fprintf(fp, "yyy\n")<0){
        perror("fprintf error"); return 1;
    }
    // 不能用 close(fd)，否则 fprintf 部分不能写入
    fclose(fp);
}

