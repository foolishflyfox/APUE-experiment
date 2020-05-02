// readlink-demo.c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <sympath>\n", argv[0]);
        return 1;
    }
    char buf[256];
    int n;
    if((n=readlink(argv[1], buf, 256))==-1){
        perror("readlink error");
        return 1;
    }else{
        buf[n] = '\0';
        printf("%s -> %s\n", argv[1], buf);
    }
}
