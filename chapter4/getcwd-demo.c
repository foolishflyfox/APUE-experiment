// getcwd-demo.c
#include <unistd.h>
#include <sys/param.h>
#include <stdio.h>
int main(){
    char buf[MAXPATHLEN];
    for(int i=0; i<MAXPATHLEN; ++i) buf[i] = 'a';
    if(getcwd(buf, MAXPATHLEN)==NULL){
        perror("getwd error");
    }else{
        printf("%s\n", buf);
    }
}

