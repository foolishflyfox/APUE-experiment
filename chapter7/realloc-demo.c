// realloc-demo.c
#include <stdio.h>
#include <stdlib.h>

int main(){
    void* p1 = malloc(8); printf("p1 = %p\n", p1);
    void* p2 = malloc(8); printf("p2 = %p\n", p2);
    p1 = realloc(p1, 20); printf("p1 = %p\n", p1);
}
