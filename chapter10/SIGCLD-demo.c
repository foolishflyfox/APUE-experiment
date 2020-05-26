// SIGCLD-demo.c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void create_child(int seconds){
    pid_t pid = fork();
    if(pid == -1){
        perror("1 fork error"); _exit(1);
    }else if(pid == 0){
        sleep(seconds);
        printf("%d exit\n", getpid());
        _exit(1);
    }
}

int main(){
    if(SIG_ERR==signal(SIGCLD, SIG_IGN)){
        perror("signal(SIGCLD) error"); return 1;
    }
    // 开辟多个子进程，只使用一个 wait
    create_child(1);
    create_child(2);
    create_child(5);
    wait(NULL);
    printf("main exit\n");
}
