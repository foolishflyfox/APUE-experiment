// chdir-demo.c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    if(creat("t1", 0644)==-1){
        perror("can't creat ./t1");
    }
    if(chdir("tmp")==-1){
        perror("can't enter tmp folder");
    }else{
        if(creat("t1", 0644)==-1){
            perror("can't creat tmp/t1");
        }
    }
}


