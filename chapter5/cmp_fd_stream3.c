// cmp_fd_stream3.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    FILE* fp = fopen("tmp", "w");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    int fd = fileno(fp);
    fwrite("abc\n", 4, 1, fp);
    write(fd, "xyz", 3);
    fclose(fp);
}
