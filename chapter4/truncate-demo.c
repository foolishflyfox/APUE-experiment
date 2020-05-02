// truncate-demo.c
#include <unistd.h>
#include <stdio.h>
int main(){
    if(truncate("tmp", 10)==-1)
        perror("Fail to truncate tmp");
}


