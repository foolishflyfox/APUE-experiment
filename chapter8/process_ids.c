// process_ids.c
#include <stdio.h>
#include <unistd.h>

int main(){
    printf("pid : %d\n", getpid());
    printf("ppid: %d\n", getppid());
    printf("uid : %u\n", getuid());
    printf("euid : %u\n", geteuid());
    printf("gid : %u\n", getgid());
    printf("egid : %u\n", getegid());
}

