// uname-demo.c
#include <stdio.h>
#include <sys/utsname.h>

int main(){
    struct utsname buf;
    if(uname(&buf)==-1){
        perror("uname error"); return 1;
    }
    printf("sysname: %s\n", buf.sysname);
    printf("nodename: %s\n", buf.nodename);
    printf("release: %s\n", buf.release);
    printf("version: %s\n", buf.version);
    printf("machine: %s\n", buf.machine);
}
