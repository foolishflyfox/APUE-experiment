// showenv.c
#include <stdio.h>

extern char** environ;

int main(int argc, char* argv[]){
    while(*environ) printf("%s\n", *environ++);
    for(int i=0; i<argc; ++i)
        printf("argv[%d]=%s\n", i, argv[i]);
}

