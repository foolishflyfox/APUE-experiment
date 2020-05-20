// setreuid-demo.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <ruid> <euid>\n", argv[0]);
        return 1;
    }
    uid_t ruid = getuid(), euid = geteuid();
    printf("1: uid = %u(%s), ", ruid, getpwuid(ruid)->pw_name);
    printf("1: euid = %u(%s)\n", euid, getpwuid(euid)->pw_name);
    uid_t t_ruid = atoi(argv[1]),  t_euid = atoi(argv[2]);
    if(-1 == setreuid(t_ruid, t_euid)){
        perror("setreuid error");
    }else{
        ruid = getuid(), euid = geteuid();
        printf("2: uid = %u(%s), ", ruid, getpwuid(ruid)->pw_name);
        printf("2: euid = %u(%s)\n", euid, getpwuid(euid)->pw_name);
    }
}

