// wait3-demo.c
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 耗时操作，n越大，用户cpu时间越多
int user_cpu(int n){
    return n<2 ? 1:user_cpu(n-1)+user_cpu(n-2);
}
// 耗时操作，n越大，系统cpu时间越多，用户cpu也会增加
void sys_cpu(int n){
    FILE* fp = tmpfile(); setbuf(fp, NULL);
    while(--n>0) fputc('a', fp);
}

int main(){
    struct rusage r;
    pid_t pid;
    if((pid=fork())<0){
        perror("fork error");
    }else if(pid==0){
        user_cpu(42);
        sys_cpu(300000);
        return 0;
    }else{
        wait3(NULL, 0, &r);
        printf("User time: %lf\n", 
            r.ru_utime.tv_sec+(double)r.ru_utime.tv_usec/1000000);
        printf("Sys time: %lf\n",
            r.ru_stime.tv_sec+(double)r.ru_stime.tv_usec/1000000);
    }
}

