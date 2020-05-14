// environ-demo.c
#include <stdio.h>

extern char** environ;

int main(int argc, char* argv[]){
    int env_cnt = 0;
    for(char** p = environ; *p!=NULL; p++, env_cnt++);
    printf("%d variants in environ\n", env_cnt);
}

