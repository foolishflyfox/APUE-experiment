// test8-5A.c
#include <unistd.h>

int main(){
    if(fork()==0){
        sleep(30);
    }else{
        sleep(10);
    }
}
