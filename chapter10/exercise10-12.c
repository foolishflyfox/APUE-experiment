// exercise10-12.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void sig_alrm(int signo){
    printf("%ld: received SIGALRM\n", time(NULL));
}
int main(){
    if(SIG_ERR == signal(SIGALRM, sig_alrm)){
        perror("signal(SIGALRM) error"); return 1;
    }
    const int bufsize = 1073741824;
    char* buf = malloc(bufsize);
    FILE* fp = fopen("tmp.out", "w");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    alarm(1);
    printf("%ld start\n", time(NULL));
    int n = fwrite(buf, 1, bufsize, fp);
    printf("write %d bytes to tmp.out\n", n);
}


