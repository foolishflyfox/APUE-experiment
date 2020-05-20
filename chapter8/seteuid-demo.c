// seteuid-demo.c
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>

void showuids(){
    uid_t c_uid, c_euid;
#ifdef __linux__
    uid_t res_uid;
    getresuid(&c_uid, &c_euid, &res_uid);
    printf("resuid = %u (%s), ", res_uid, getpwuid(res_uid)->pw_name);
#else
    c_uid = getuid(), c_euid = geteuid();
#endif
    printf("uid = %u (%s), ", c_uid, getpwuid(c_uid)->pw_name);
    printf("euid = %u (%s)\n", c_euid, getpwuid(c_euid)->pw_name);
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <euid>\n", argv[0]);
        return 1;
    }
    uid_t euid0 = geteuid();
    uid_t euid1 = atoi(argv[1]);
    showuids();
    if(-1==seteuid(euid1)){
        perror("1 seteuid error"); return 1;
    }
    showuids();
    if(-1==seteuid(euid0)){
        perror("2 seteuid error"); return 1;
    }
    showuids();
}
