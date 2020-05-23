// 9-12.c
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

static void sig_hup(int signo){
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}
static void pr_ids(char* name){
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
        name, (long)getpid(), (long)getppid(), (long)getpgrp(),
        (long)tcgetpgrp(STDIN_FILENO));
}

int main(){
    char c;
    pid_t pid;
    pr_ids("parent");
    if((pid=fork()) < 0){
        perror("fork error"); return 1;
    }else if(pid==0){
        pr_ids("child");
        signal(SIGHUP, sig_hup);  /* 子进程注册 SIGHUP 处理函数 */
        kill(getpid(), SIGTSTP);  /* 向自己发送 SIGTSTP 信号 */
        pr_ids("child");          /* 只有在收到 SIGCONT 才能打印 */
        if(read(STDIN_FILENO, &c, 1) != 1)
            printf("read error %d on controlling TTY\n", errno);
    }else{
        sleep(5);
    }
    _exit(0);
}

