// getenv-demo.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <VAR>\n", argv[0]); return 1;
    }
    const char* var;
    if((var=getenv(argv[1]))==NULL){
        printf("There isn't %s in environment\n", argv[1]);
    }else{
        printf("%s=%s\n", argv[1], var);
    }
}
