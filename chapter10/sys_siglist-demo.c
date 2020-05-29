// sys_siglist-demo.c
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    for(int i=1; i<32; ++i){
#ifdef __APPLE__
        char* str = strdup(sys_signame[i]);
        for(char* p=str; *p!='\0'; ++p) *p = toupper(*p);
        printf("SIG%-7s(%2d):\t%s\n", str, i, sys_siglist[i]);
        free(str);
#else
        printf("%d:%s %c", i, sys_siglist[i], "\n "[(i+1)%4!=0]);
#endif
    }
}
