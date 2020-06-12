// 15-11.c
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024
#define  DEF_PAGER "${PAGER:-more}"  /* environment variable, or default */

int main(int argc, char* argv[]){
    char line[MAXLINE];
    FILE *fpin, *fpout;
    if(argc!=2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]); exit(1);
    }
    if((fpin = fopen(argv[1], "r")) == NULL){
        perror("fopen error"); exit(1);
    }
    if((fpout = popen(DEF_PAGER, "w")) == NULL){
        perror("popen error"); exit(1);
    }
    /* copy argv[1] to pager */
    while(fgets(line, MAXLINE, fpin) != NULL){
        if(fputs(line, fpout) == EOF){
            perror("fputs error to pipe"); exit(1);
        }
    }
    if(ferror(fpin)) {
        perror("fgets error"); exit(1);
    }
    if(pclose(fpout) == -1){
        perror("pclose error"); exit(1);
    }
}

