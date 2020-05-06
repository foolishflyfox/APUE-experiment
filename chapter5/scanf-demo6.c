// scanf-demo6.c
#include <stdio.h>

int main(){
    int a, b, c, d, e, f;
    scanf("%d %i %i %o %u %x",&a,&b,&c,&d,&e,&f);
    printf("%d %d %d %d %d %d\n",a,b,c,d,e,f);
    char s1[64], s2[64];
    scanf("%[ abc] %[^a-c]", s1, s2);
    printf("s1=\"%s\", s2=\"%s\"\n",s1,s2);
}
