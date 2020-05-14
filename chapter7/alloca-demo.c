// alloca-demo.c
#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    void* p1 = malloc(128);
    void* p2 = alloca(128);
    printf(" p1 = %p,  p2 = %p\n", p1, p2);
    printf("&p1 = %p, &p2 = %p\n", &p1, &p2);
    free(p1);
}

