// append.c
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd1 = open("append.txt", O_WRONLY | O_APPEND);
    int fd2 = open("n.txt", O_WRONLY | O_APPEND | O_CREAT, 0600);
    const char* s = "HELLO,WORLD\n";
    write(fd1, s, strlen(s)); write(fd2, s, strlen(s));
    close(fd1); close(fd2);
}
