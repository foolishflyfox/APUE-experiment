// control-flow.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define BSZ 1024
int main(){
    FILE *fd_b, *fd_c;
    if((fd_b = popen("./b.out", "r"))==NULL) {
        perror("popen ./b.out error"); exit(1);
    }
    if((fd_c = popen("./c.out", "w"))==NULL) {
        perror("popen ./c.out error"); exit(1);
    }
    char buf[BSZ];
    if(fgets(buf, BSZ, fd_b)==NULL){ perror("fgets error"); exit(1); }
    if(fprintf(fd_c, "%s", buf)<0){perror("fprintf error"); exit(1); }
    int bret = pclose(fd_b), cret = pclose(fd_c); 
    printf("bret=%d,  cret=%d\n", WEXITSTATUS(bret), WEXITSTATUS(cret));
}
