// setuid-demo.c
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

int main(int argc, char* argv[]){
    if(argc==2){
        uid_t uid = (uid_t)atoi(argv[1]);
        if(-1==setuid(uid)){
            perror("setuid error");
            return 1;
        }
    }
    uid_t c_uid, c_euid;
#ifdef __linux__
    uid_t res_uid;
    getresuid(&c_uid, &c_euid, &res_uid);
    printf("resuid = %u (%s)\n", res_uid, getpwuid(res_uid)->pw_name);
#else
    c_uid = getuid(), c_euid = geteuid();
#endif
    printf("uid = %u (%s)\n", c_uid, getpwuid(c_uid)->pw_name);
    printf("euid = %u (%s)\n", c_euid, getpwuid(c_euid)->pw_name);
}

