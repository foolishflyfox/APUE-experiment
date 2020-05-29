// exercise10-6.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) { sigflag = 1; }

void TELL_WAIT(){
    if(signal(SIGUSR1, sig_usr) == SIG_ERR){
        perror("signal(SIGUSR1) error"); _exit(1);
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR){
        perror("signal(SIGUSR2) error"); _exit(1);
    }
    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        perror("SIG_BLOCK error"); _exit(1);
    }
}
void WAIT_PARENT(){
    while(sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); _exit(1);
    }
}
void WAIT_CHILD(){
    while(sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        perror("SIG_SETMASK error"); _exit(1);
    }
}
void TELL_PARENT(pid_t pid){
    kill(pid, SIGUSR2);
}
void TELL_CHILD(pid_t pid){
    kill(pid, SIGUSR1);
}
int readval(FILE* fp){
    if(-1==fseek(fp, SEEK_SET, 0)){
        perror("readval error"); exit(1);
    }
    int val;
    if(fscanf(fp, "%d", &val)<1){
        perror("fscanf error"); exit(1);
    }
    return val;
}
void writeval(FILE* fp, int val){
    if(-1==fseek(fp, SEEK_SET, 0)){
        perror("readval error"); exit(1);
    }
    if(fprintf(fp, "%d", val) < 0){
        perror("fprintf error"); exit(1);
    }
    fflush(fp);
}
int main(){
    FILE* fp = fopen("tmp.txt", "w+");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    fprintf(fp, "%d", 0);
    fflush(fp);
    TELL_WAIT(); 
    pid_t pid = fork();
    if(pid==-1){
        perror("fork error"); return 1;
    }else if(pid==0){
        for(; ;){
            int val = readval(fp)+1;
            writeval(fp, val);
            printf("child write %d\n", val);
            sleep(1);
            TELL_PARENT(getppid());
            WAIT_PARENT();
        }
    }else{
        for(; ;){
            WAIT_CHILD();
            int val = readval(fp)+1;
            writeval(fp, val);
            printf("parent write %d\n", val);
            sleep(1);
            TELL_CHILD(pid);
        }
    }

}
