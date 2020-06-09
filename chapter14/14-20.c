// 14-20.c
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BSZ 4096
unsigned char buf[BSZ];

unsigned char translate(unsigned char c){
    if(isalpha(c)){
        if(c >= 'n') c -= 13;
        else if(c >= 'a')  c += 13;
        else if(c >= 'N') c-= 13;
        else c += 13;
    }
    return c;
}
int main(int argc, char* argv[]){
    int ifd, ofd, i, n, nw;
    if(argc != 3){
        printf("Usage: %s infile outfile\n", argv[0]); exit(1);
    }
    if( (ifd = open(argv[1], O_RDONLY)) < 0 ){
        fprintf(stderr, "can't open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    if( (ofd = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0644)) < 0 ){
        fprintf(stderr, "can't create %s: %s\n", argv[2], strerror(errno));
        exit(1);
    }
    while((n = read(ifd, buf, BSZ)) > 0){
        for(i = 0; i<n; ++i) buf[i] = translate(buf[i]);
        if((nw = write(ofd, buf, n)) != n){
            if(nw < 0){
                perror("write failed"); exit(1);
            }else{
                fprintf(stderr, "short write (%d/%d)\n", nw, n);
                exit(1);
            }
        }
    }
    fsync(ofd);
}
