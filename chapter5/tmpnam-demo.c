// tmpnam.c
#include <stdio.h>

int main(){
    printf("TMP_MAX = %d\n", TMP_MAX);
    printf("L_tmpnam = %d\n", L_tmpnam);
    char* s1 = tmpnam(NULL);
    printf("s1 = %s\n", s1);
    char* s2 = tmpnam(NULL);
    printf("s1 = %s, s2 = %s\n", s1, s2);
}
