// execle-demo.c
#include <unistd.h>
#include <stdio.h>

int main(){
    const char* envp[] = {"X=10", "Y=20", NULL};
    if(execle("./tmp.out", "nnn", "mmm", NULL, envp)==-1){
        perror("execle error");
    }
}
