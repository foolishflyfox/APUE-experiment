// access-demo.c
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: %s <pathname>\n", argv[0]);
        return 1;
    }
    if(access(argv[1], F_OK)<0){
        printf("%s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    if(access(argv[1], R_OK)<0){
        printf("access error for %s: %s\n", argv[0], strerror(errno));
    }else{
        printf("read access OK\n");
    }
    if(open(argv[1], O_RDONLY) < 0){
        printf("open error for %s: %s\n", argv[0], strerror(errno));
    }else{
        printf("open for reading OK\n");
    }
}
