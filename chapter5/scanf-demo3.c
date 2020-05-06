// scanf-demo3.c
#include <stdio.h>

int main(){
    char s1[64], s2[64];
    int a;
    float b;
    scanf("%3d %4s %5f %s", &a, s1, &b, s2);
    printf("a=%d, s1=\"%s\", b=%g, s2=\"%s\"\n",a, s1, b, s2);
}
