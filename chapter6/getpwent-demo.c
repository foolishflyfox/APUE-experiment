// getpwent-demo.c
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>

void show_passwd_entry(struct passwd* p_passwd){
    printf("Username : %s\n", p_passwd->pw_name);
    printf("Password : %s\n", p_passwd->pw_passwd);
    printf("User ID  : %u\n", p_passwd->pw_uid);
    printf("Group ID : %u\n", p_passwd->pw_gid);
    printf("Real name: %s\n", p_passwd->pw_gecos);
    printf("Home path: %s\n", p_passwd->pw_dir);
    printf("Shell    : %s\n", p_passwd->pw_shell);
}

struct passwd* mygetpwname(const char* name){
    struct passwd *ptr;
    while((ptr=getpwent())!=NULL){
        if(strcmp(name, ptr->pw_name)==0){
            break;
        }
    }
    endpwent();
    return ptr;
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <uid>\n", argv[0]); return 1;
    }
    struct passwd* p_passwd = mygetpwname(argv[1]);
    if(p_passwd==NULL){
        fprintf(stderr, "no uid equal to %s\n", argv[1]); return 1;
    }
    show_passwd_entry(p_passwd);
}
