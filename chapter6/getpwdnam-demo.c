// getpwnam-demo.c
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>

void show_passwd_entry(struct passwd* p_passwd){
    printf("Username : %s\n", p_passwd->pw_name);
    printf("Password : %s\n", p_passwd->pw_passwd);
    printf("User ID  : %u\n", p_passwd->pw_uid);
    printf("Group ID : %u\n", p_passwd->pw_gid);
    printf("Real name: %s\n", p_passwd->pw_gecos);
    printf("Home path: %s\n", p_passwd->pw_dir);
    printf("Shell    : %s\n", p_passwd->pw_shell);
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <user>\n", argv[0]); return 1;
    }
    uid_t uid = atoi(argv[1]);
    struct passwd* p_passwd = getpwnam(argv[1]);
    if(p_passwd==NULL){
        fprintf(stderr, "no user named %s\n", argv[1]); return 1;
    }
    show_passwd_entry(p_passwd);
}
