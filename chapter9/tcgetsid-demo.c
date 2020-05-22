// tcgetsid-demo.c
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

int main(){
    int fd = open("/dev/tty", O_RDONLY);
    printf("sid = %d\n", tcgetsid(fd));
}
