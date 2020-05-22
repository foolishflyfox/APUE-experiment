// exercise8-3.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void show_siginfo(siginfo_t* pinfo){
    switch(pinfo->si_code){
        case CLD_EXITED:
            printf("normal termination, exit status is %d\n",
                    pinfo->si_status);
            break;
        case CLD_DUMPED:
            printf("abnormal termination, signal number is %d %s\n",
                    pinfo->si_status, ", core file generated");
            break;
        case CLD_KILLED:
            printf("abnormal termination, signal number is %d %s\n",
                    pinfo->si_status, ", no core file");
            break;
        case CLD_STOPPED:
            printf("child stopped, signal number = %d\n",
                    pinfo->si_status);
            break;
    }
}

int main(){
    pid_t pid;
    int status;
    siginfo_t info;
    
    if((pid = fork())<0){ perror("1 fork error");}
    else if(pid==0){ exit(7); }
    if(-1==waitid(P_ALL, 0, &info, WEXITED)) perror("1 waitid error");
    show_siginfo(&info);

    if((pid = fork())<0) { perror("2 fork error"); }
    else if(pid==0) {abort();}
    if(-1==waitid(P_ALL, 0, &info, WEXITED)) perror("2 waitid error");
    show_siginfo(&info);

    if((pid = fork())<0) { perror("3 fork error"); }
    else if(pid==0) {status /= 0;}
    if(-1==waitid(P_ALL, 0, &info, WEXITED)) perror("3 waitid error");
    show_siginfo(&info);
}


