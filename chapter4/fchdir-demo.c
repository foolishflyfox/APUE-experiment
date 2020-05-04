// fchdir-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <fcntl.h>

void show_cwd(){
    char buf[MAXPATHLEN];
    if(getcwd(buf, MAXPATHLEN)==NULL){
        perror("show_cwd error");
    }else{
        printf("%s\n", buf);
    }
}
void do_something(){
    show_cwd();
}
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dirpath>\n", argv[0]);
        return 1;
    }
    show_cwd();
    int cwd_fd = open(".", O_DIRECTORY);
    printf("change cwd to %s\n", argv[1]);
    if(chdir(argv[1])==-1){
        perror("chdir error"); return 1;
    }
    do_something();
    if(fchdir(cwd_fd)==-1){
        perror("chdir to cwd error"); return 1;
    }
    show_cwd();
}

