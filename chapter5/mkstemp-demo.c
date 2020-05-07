// mkstemp-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

void make_temp(char *template);

int main(){
    char good_template[] = "/tmp/dirXXXXXX"; /* right way */
    char* bad_template = "/tmp/dirXXXXXX";   /* wrong way */
    printf("trying to create first tmp file...\n");
    make_temp(good_template);
    printf("tring to create second tmp file...\n");
    make_temp(bad_template);
}
void make_temp(char* template){
    int fd;
    struct stat sbuf;
    if((fd = mkstemp(template))<0){
        perror("can't create temp file"); return;
    }
    printf("temp name = %s\n", template);
    close(fd);
    if(stat(template, &sbuf) < 0){
        if(errno==ENOENT){
            printf("file doesn't exist\n");
        }else{
            perror("stat failed");
        }
    }else{
        printf("file exists\n");
        unlink(template);
    }
}
