// rmdir-demo.c
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dir-path>\n", argv[0]);
        return 1;
    }
    if(rmdir(argv[1]) < 0){
        perror("rmdir error");
        return 1;
    }
}

