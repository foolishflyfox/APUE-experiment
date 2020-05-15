// environ-demo2.c
#include <stdio.h>

extern char** environ;

int main(int argc, char* argv[]){
    int a = 10;
    printf("        &a = %p\n", &a);
    printf("   environ = %p\n", environ);
    printf("environ[0] = %p\n", environ[0]);
}

