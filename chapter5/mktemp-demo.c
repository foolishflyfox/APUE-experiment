// mktemp-demo.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    char nm[] = "abc.XXXXXX";
    printf("mktemp return \"%s\"\n", mktemp(nm));
    printf("nm = \"%s\"\n", nm);
}

