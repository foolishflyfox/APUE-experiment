// getlogin-demo.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    extern char** environ;
    for(char** p = environ; *p; ++p){
        if(strncmp("LOGNAME=", *p, 8)==0){
            printf("%s\n", *p);
            break;
        }
    }
    const char* logname;
    if(NULL == (logname=getlogin())){
        perror("getlogin error");
    }else{
        printf("getlogin result: %s\n", logname);
    }
}

