// sigttin-demo.c
#include <unistd.h>
int main(){
    sleep(2);
    char c;
    read(STDIN_FILENO, &c, 1);
}
