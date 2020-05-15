// setenv-demo3.c
#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <name=value>\n", argv[0]);
        return 1;
    }
    printf("%p\n", environ);
    if(putenv(argv[1])==-1){
        perror("putenv error");
    }else{
        printf("%p\n", environ);
    }
}
