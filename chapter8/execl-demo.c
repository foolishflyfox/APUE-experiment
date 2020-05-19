// execl-demo.c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }
    if(execl(argv[1], "5", "6", "7", (char*)0)==-1){
        perror("execl error");
    }
}
