// symlink-demo.c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <actualpath> <sympath>\n", argv[0]);
        return 1;
    }
    if(symlink(argv[1], argv[2])==-1){
        perror("symlink error");
        return 1;
    }
}

