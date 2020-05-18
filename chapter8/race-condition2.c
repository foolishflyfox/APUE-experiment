// race-condition2.x
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

static void charatatime(char *str){
    char* ptr;
    int c;
    setbuf(stdout, NULL);  /* 设置标准输出为无缓冲模式 */
    for(ptr = str; (c=*ptr)!=0; ++ptr)
        putc(c, stdout);
}
static int fds[2];
void TELL_WAIT(){ if(pipe(fds)==-1) perror("pipe error"); }
void WAIT_PARENT(){ close(fds[1]); read(fds[0], NULL, 1); }
void TELL_CHILD(){ close(fds[0]); close(fds[1]); }
void WAIT_CHILD(){ wait(NULL); }

int main(){
    pid_t pid;
    TELL_WAIT();
    if((pid=fork())<0){
        perror("fork error");
    }else if(pid==0){
        WAIT_PARENT();
        charatatime("output from child\n");
    }else {
        charatatime("output from parent\n");
        TELL_CHILD();
        WAIT_CHILD();
    }
    return 0;
}
