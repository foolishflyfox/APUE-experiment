// blk-demo.c
#include <sys/stat.h>
#include <stdio.h>

int main(){
    struct stat buf;
    if(stat("tmp", &buf)<0){
        perror("can't get tmp state");
    }else{
        printf("blksize=%d, blocks=%lld\n",buf.st_blksize,buf.st_blocks);
    }
}

