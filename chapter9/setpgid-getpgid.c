// setpgid-getpgid.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void show_ids(){
    // getpgrp 等价于 getpgid(0)
    printf("ppid = %d, pid = %d, pgid = %d\n", 
            getppid(), getpid(), getpgrp());
}

int main(int argc, char* argv[]){
    pid_t pid;
    if(argc > 1){
        sleep(2); show_ids();
        printf("child change pgid\n");
        if(-1==setpgid(getpid(), getpid())){
            perror("4 setpgid error"); return 1;
        }
        show_ids();
        return 0;
    }else{
        show_ids();
        if(-1==setpgid(getpid(), getpgid(getppid()))){
            perror("0 setpgid error"); return 1;
        }
        show_ids();
    }

    if(-1==(pid=fork())){
        perror("fork error"); return 1;
    }else if(pid==0){
        show_ids();
        sleep(2);
        show_ids();
        sleep(2);
        show_ids();
        execl(argv[0], argv[0], "x", NULL);
        _exit(0);
    }else{
        sleep(1);
        printf("%d set %d pgid to %d\n", getpid(), pid, pid);
        if(-1==setpgid(pid, pid)) perror("1 setpgid error");
        sleep(2);
        printf("%d set %d pgid to %d\n", getpid(), pid, getpgid(0));
        if(-1==setpgid(pid, getpgid(0))) perror("2 setpgid error");
        sleep(2);
        printf("%d set %d pgid to %d\n", getpid(), pid, pid);
        if(-1==setpgid(pid, pid)) perror("3 setpgid error");
    }
    wait(NULL);
}

