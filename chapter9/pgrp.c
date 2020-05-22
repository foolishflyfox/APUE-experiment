// pgrp.c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("%s: pid = %d\n", argv[0], getpid());
    fgetc(stdin);
}
