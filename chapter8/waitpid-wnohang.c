// waitpid-wnohang.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int pid1 = fork();
    if(pid1 == -1) { perror("1 fork error"); return 1; }
    if(pid1==0){
        sleep(5); return 0;
    }
    int pid2 = fork();
    if(pid2 == -1) { perror("2 fork error"); return 1; }
    if(pid2 == 0) return 0;
    printf("pid1 = %d, pid2 = %d\n", pid1, pid2);
    sleep(1);
    int s1, s2;
    int ret1 = waitpid(pid1, &s1, WNOHANG);
    int ret2 = waitpid(pid2, &s2, WNOHANG);
    printf("ret1 = %d, ret2 = %d\n", ret1, ret2);
    printf("1 exit: %d,    2 exit:%d\n", WIFEXITED(s1), WIFEXITED(s2));
}

