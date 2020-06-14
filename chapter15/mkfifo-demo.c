// mkfifo-demo.c
#include <stdio.h>
#include <sys/stat.h>

int main(){
    const char* fifo_name = "tmp.pip";
    if(mkfifo(fifo_name, 0644) == -1){
        perror("mkfifo error"); return 1;
    }
    struct stat buf;
    if(lstat(fifo_name, &buf)==-1){
        perror("lstat error"); return 1;
    }
    printf("%s is%s FIFO\n", fifo_name, S_ISFIFO(buf.st_mode)?"":"'t");
}
