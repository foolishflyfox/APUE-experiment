// cp-osync-fsync.c
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if(argc < 4){
        fprintf(stderr, "Usage: %s src dst bufsize\n", argv[0]);
        return 1;
    }
    int fd_src = open(argv[1], O_RDONLY);
    int fd_dst = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, 0644);
    size_t bufsize = atoi(argv[3]);
    char* buf = malloc(bufsize);
    int sz = 0, loops = 0;
    while((sz = read(fd_src, buf, bufsize)) > 0)
        write(fd_dst, buf, sz), fsync(fd_dst), loops++;
    if(sz>-1) printf("Copy finished, loops %d\n", loops);
    else printf("Something is wrong\n");
    close(fd_src); close(fd_dst); free(buf);
}

