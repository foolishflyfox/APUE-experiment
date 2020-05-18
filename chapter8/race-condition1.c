// race-condition1.x
#include <stdio.h>
#include <unistd.h>

static void charatatime(char *str){
    char* ptr;
    int c;
    setbuf(stdout, NULL);  /* 设置标准输出为无缓冲模式 */
    for(ptr = str; (c=*ptr)!=0; ++ptr)
        putc(c, stdout);
}

int main(){
    pid_t pid;
    if((pid=fork())<0){
        perror("fork error");
    }else if(pid==0){
        charatatime("output from child\n");
    }else {
        charatatime("output from parent\n");
    }
    return 0;
}
