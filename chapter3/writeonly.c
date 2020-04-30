// writeonly.c
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd = open("wo.txt", O_WRONLY);
    const char* s = "HELLO,WORLD\n";
    write(fd, s, strlen(s));
    close(fd);
}
