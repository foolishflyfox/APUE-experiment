// show-user.c
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    struct passwd* pw = getpwuid(uid);
    if(pw) printf(" UID = %u [%s]\n", uid, pw->pw_name);
    else perror("first getpwuid error");
    pw = getpwuid(euid);
    if(pw) printf("EUID = %u [%s]\n", euid, pw->pw_name);
    else perror("second getpwuid error");
}

