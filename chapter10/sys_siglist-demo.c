// sys_siglist-demo.c
#include <stdio.h>

extern char* sys_siglist[];

int main(){
    for(int i=0; i<32; ++i)
        printf("%d:%s %c", i, sys_siglist[i], "\n "[(i+1)%4!=0]);
}
