// re-in.c
#include <unistd.h>
#include <string.h>
int main(){
    char *msg1="Normal Message\n", *msg2="Error Message\n";
    write(STDOUT_FILENO, msg1, strlen(msg1));
    write(STDERR_FILENO, msg2, strlen(msg2));
}

