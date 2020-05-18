// TOCTTOU-demo.c
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 256

int is_safe(const char* path){
    // check 检查文件，只能执行 echo right
    FILE* fp;
    char buf[256];
    if((fp=fopen(path, "r"))==NULL){
        perror("fopen error"); return 0;
    }
    while(fgets(buf, BUFSIZ, fp)){
        if(strncmp("echo right", buf, 10)!=0) return 0;
    }
    fclose(fp);
    return 1;
}

int main(){
    const char* path = "./test.sh";
    if(is_safe(path)){
        sleep(10);
        printf("begin to exec %s\n", path);
        if(execlp(path, path, NULL)==-1)
            perror("execlp error");
    }
}

