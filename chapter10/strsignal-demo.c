// strsignal-demo.c
#include <string.h>
#include <stdio.h>
#include <signal.h>
int main(){
    printf("SIGALRM: %s\n", strsignal(SIGALRM));
}
