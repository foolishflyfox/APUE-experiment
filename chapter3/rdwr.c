// rdwr.c
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd = open("rdwr.txt", O_RDWR);
    const char* s = "HELLO,WORLD\n";
    write(fd, s, strlen(s));
    close(fd);
}
