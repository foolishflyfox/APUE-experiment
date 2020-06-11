// cp-rw.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BSZ 8192
int main(int argc, char* argv[]){
    int fdin, fdout, n;
    if(argc!=3){ 
        fprintf(stderr, "Usage: %s <fromfile> <tofile>\n", argv[0]);
        return 1; 
    }
    if((fdin = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "open %s error\n", argv[1]); return 1;
    }
    if((fdout = open(argv[2], O_RDWR|O_TRUNC|O_CREAT, 0644)) < 0){
        fprintf(stderr, "open %s error\n", argv[2]); return 1;
    }
    char buf[BSZ];
    while((n = read(fdin, buf, BSZ)) > 0){
        if(write(fdout, buf, n)!=n){
            perror("write error"); return 1;
        }
    }
    if(n < 0) { perror("read error"); return 1; }
    return 0;
}
