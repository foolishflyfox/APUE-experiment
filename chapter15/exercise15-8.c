// exercise15-8.c
#include <stdio.h>
#include <unistd.h>
#define BUFSZ 512
int main(int argc, char* argv[]){
    FILE *fp = popen("./hw.out", "r");
    printf("%s pid = %d\n", argv[0], getpid());
    if(fp==NULL) { perror("popen error"); return 1; }
    char buf[BUFSZ];
    if(fscanf(fp, "%s", buf)!=1){ perror("fscanf error"); }
    else { printf("GET: %s\n", buf); }
}

