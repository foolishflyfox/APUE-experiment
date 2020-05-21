// nice-demo.c
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){
    // 获取初始nice值
    errno = 0;
    int n1 = nice(0);
    if(n1==-1 && errno){
        perror("first nice error"); return 1;
    }
    printf("n1 = %d\n", n1);
    int n2 = nice(5);
    if(n2==-1 && errno){
        perror("first nice error"); return 1;
    }
    printf("n2 = %d\n", n2);
    int n3 = nice(-2);
    if(n3==-1 && errno){
        perror("third nice error"); return 1;
    }
    printf("n3 = %d\n", n3);
}

