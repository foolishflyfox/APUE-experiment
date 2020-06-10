// 14-27.c
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define COPYINCR    (1024*1024*1024)    /*1 GB*/
int main(int argc, char* argv[]){
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;
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
    if(fstat(fdin, &sbuf) < 0){  // need size of input file
        perror("fstat error"); return 1;
    }
    if(ftruncate(fdout, sbuf.st_size) < 0){
        perror("ftruncate error"); return 1;
    }
    while(fsz < sbuf.st_size){
        if((sbuf.st_size - fsz) > COPYINCR) copysz = COPYINCR;
        else copysz = sbuf.st_size - fsz;
        src = mmap(NULL, copysz, PROT_READ, MAP_SHARED, fdin, fsz);
        if(MAP_FAILED==src) { perror("mmap error for input"); return 1; }
        dst = mmap(NULL, copysz, PROT_READ|PROT_WRITE, MAP_SHARED, fdout, fsz);
        if(MAP_FAILED == dst) { perror("mmap error for output"); return 1; }
        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
}
