// wait-demo2.c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

pid_t mywaitpid(pid_t pid, int* status){
    static size_t cnt = 0;
    static int infos[64][2];
    pid_t tp;
    for(int i=0; i<cnt; ++i){
        if(infos[i][0]==pid){
            *status = infos[i][1];
            infos[i][0] = infos[cnt-1][0];
            infos[i][1] = infos[cnt-1][1];
            cnt--;
            return pid;
        }
    }
    while((tp=wait(status))!=pid){
        infos[cnt][0] = tp;
        infos[cnt][1] = *status;
        cnt++;
    }
    return pid;
}

int main(){
    pid_t p1, p2, p3;
    if((p1=fork())==0){
        sleep(3);
        exit(1);
    }
    if((p2=fork())==0){
        sleep(2);
        exit(2);
    }
    if((p3=fork())==0){
        sleep(1);
        exit(3);
    }
    int x;
    mywaitpid(p1, &x); printf("%d exit\n", WEXITSTATUS(x));
    mywaitpid(p2, &x); printf("%d exit\n", WEXITSTATUS(x));
    mywaitpid(p3, &x); printf("%d exit\n", WEXITSTATUS(x));
}

