// 10-15.c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <string.h>

void my_alarm(int signo){
    struct passwd* rootptr;
    printf("in signal handler\n");
    if((rootptr = getpwnam("root"))==NULL){
        perror("getpwnam(root) error");
    }
    alarm(1);
}

int main(int argc, char* argv[]){
    struct passwd* ptr;
    if(argc!=2){
        fprintf(stderr, "Usage: %s <username>\n", argv[0]); return 1;
    }
    signal(SIGALRM, my_alarm);
    alarm(1);
    for( ; ;) {
        if(NULL==(ptr=getpwnam(argv[1]))){
            perror("getpwnam error"); return 1;
        }
        if(strcmp(ptr->pw_name, argv[1])!=0){
            printf("return value corrupted!, pw_name = %s\n",
                ptr->pw_name);
        }
    }
}
