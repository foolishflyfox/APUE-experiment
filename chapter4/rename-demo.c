// rename-demo.c
#include <stdio.h>
int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stdout, "Usage: %s old-name new-name\n", argv[0]);
        return 1;
    }
    if(rename(argv[1], argv[2])==-1){
        perror("rename error"); return 1;
    }
}

