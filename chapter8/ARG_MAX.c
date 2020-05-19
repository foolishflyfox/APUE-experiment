// ARG_MEX.c
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("_SC_ARG_MAX = %ld\n", (long)sysconf(_SC_ARG_MAX));
}
