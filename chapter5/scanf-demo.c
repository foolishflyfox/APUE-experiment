// scanf-demo.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int a=0, b=0, c=0, d=0;
    int n = scanf("%d %d %d %d\n", &a, &b, &c, &d);
    printf("%d: %d,%d,%d,%d\n", n, a, b, c, d);
}
