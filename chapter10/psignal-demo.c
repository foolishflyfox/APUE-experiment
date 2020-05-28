// psignal-demo.c
#include <stdio.h>
#include <signal.h>

int main(int argc, char* argv[]){
    for(int i=0; i<32; ++i)
        psignal(i, argv[0]);
}
