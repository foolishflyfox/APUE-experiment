// show-args.c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    for(int i=0; i<argc; ++i)
        printf("argv[%d]=%s   %c", i, argv[i], " \n"[i==argc-1]);
}
