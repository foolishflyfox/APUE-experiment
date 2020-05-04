// mkdir-demo.c
#include <sys/stat.h>
#include <stdio.h>
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dir-path>\n", argv[0]);
        return 1;
    }
    if(mkdir(argv[1], 0755)<0){
        perror("mkdir error");
        return 1;
    }
}

