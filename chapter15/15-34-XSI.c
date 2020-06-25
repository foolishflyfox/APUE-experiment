// 15-34-XSI.c
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef __APPLE__
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
#endif
int id;
struct sembuf p = {0, -1, SEM_UNDO};  // 索引为0的信号量值减1
struct sembuf v = {0, 1, SEM_UNDO};  // 索引为0的信号量值加1
void opts(){
    for(int i=0; i<1000000; ++i){
        if(semop(id, &p, 1)<0){ perror("semop P error"); return; }
        if(semop(id, &v, 1)<0){ perror("semop V error"); return; }
    }
}
int main(){
    key_t semkey = 0x123456;
    if((id= semget(semkey, 1, 0666))==-1){  // 如果信号量集不存在，则新建
        printf("create semophore set\n");
        // 该信号量集中仅有一个信号量
        id = semget(semkey, 1, 0666|IPC_CREAT);
        if(id < 0){ perror("semget error"); exit(1); }
        // 初始化信号量集中的信号量(致命缺点，创建与初始化非原子操作)
        union semun u;
        u.val = 1;  // 指定该信号量集信号量的资源为1
        // 对 信号量0 进行设置
        if(semctl(id, 0, SETVAL, u) < 0){
            perror("semctl error"); exit(1);
        }
    }
    pid_t pid1, pid2;
    if((pid1=fork())==-1){ perror("fork 1 error"); exit(1); }
    if(pid1==0) { opts(); exit(0); }
    if((pid2=fork())==-1){ perror("fork 2 error"); exit(1); }
    if(pid2==0) { opts(); exit(0); }
    opts();
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

