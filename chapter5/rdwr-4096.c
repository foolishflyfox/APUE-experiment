// rdwr-4096.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFSIZE 4096

int main(){
    char buf[BUFFSIZE];
    int cnt = 0;
    while((cnt=read(STDIN_FILENO, buf, BUFFSIZE))>0){
        if(write(STDOUT_FILENO, buf, cnt) != cnt){
            perror("write error"); return 1;
        }
    }
    if(cnt<0){
        perror("read error"); return 1;
    }
}
