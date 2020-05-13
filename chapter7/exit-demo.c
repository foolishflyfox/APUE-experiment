// exit-demo.c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: %s <return|exit|_Exit|_exit>\n", argv[0]);
        return 1;
    }
    if(strcmp(argv[1], "return")==0){
        FILE* fp = fopen("tmp.1", "w");
        fprintf(fp, "test return\n");
    }else if(strcmp(argv[1], "exit")==0){
        FILE* fp = fopen("tmp.2", "w");
        fprintf(fp, "test exit\n");
        exit(0);
    }else if(strcmp(argv[1], "_exit")==0){
        FILE* fp = fopen("tmp.3", "w");
        fprintf(fp, "test _exit\n");
        _exit(0);
    }else if(strcmp(argv[1], "_Exit")==0){
        FILE* fp = fopen("tmp.4", "w");
        fprintf(fp, "test _Exit\n");
        _Exit(0);
    }
    return 0;
}

