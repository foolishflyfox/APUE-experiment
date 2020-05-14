// argvs.c
#include <stdio.h>

int main(int argc, char* argv[]){
    for(char** p = argv; *p!=NULL; ++p) printf("%s\n", *p);
}
