// alloc-demo.c
#include <stdlib.h>
#include <stdio.h>

int main(){
    unsigned char *p1, *p2;
    p1 = malloc(4); p1[0] = 1; p1[1]=2; p1[2]=3; p1[3]=4;
    printf("p1 = %p\n", p1);
    free(p1);
    p1 = malloc(4);
    p2 = calloc(4, 1); p2[0] = 1; p2[1]=2; p2[2]=3; p2[3]=4;
    printf("p2 = %p\n", p2);
    free(p2);
    p2 = calloc(4, 1);
    printf("p1(%p): %x %x %x %x\n", p1, p1[0], p1[1], p1[2], p1[3]);
    printf("p2(%p): %x %x %x %x\n", p2, p2[0], p2[1], p2[2], p2[3]);
}

