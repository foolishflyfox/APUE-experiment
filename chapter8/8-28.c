// 8-28.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>

int main(){
    pid_t pid;
    // 父进程
    if(-1==(pid=fork())){
        perror("1 fork error"); return 1;
    }else if(pid > 0){
        sleep(2);
        exit(2);
    }
    // 第一个子进程
    if(-1==(pid=fork())){
        perror("2 fork error"); return 1;
    }else if(pid > 0){
        sleep(4);
        abort();
    }
    // 第二个子进程
    if(-1==(pid=fork())){
        perror("3 fork error"); return 1;
    }else if(pid > 0){
        execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
        // 正常来说下面的 exit 不会被执行
        exit(7);
    }
    // 第三个子进程
    if(-1==(pid=fork())){
        perror("4 fork error"); return 1;
    }else if(pid > 0){
        sleep(8);
        exit(0);
    }
    // 第四个子进程
    sleep(6);
    kill(getpid(), SIGKILL);
    // 由于 kill 函数，下面的 exit 不会被执行
    exit(6);
}


