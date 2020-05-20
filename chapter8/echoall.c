// echoall.c
#include <stdio.h>

int main(int argc, char* argv[]){
    extern char **environ;
    for(int i=0; i<argc; ++i) printf("argv[%d]: %s\n", i, argv[i]);
    for(char** ptr = environ; *ptr!=NULL; ptr++) printf("%s\n", *ptr);
    return 0;
}
