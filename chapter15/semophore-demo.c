// semophore-demo.c
#include <stdio.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#ifndef __APPLE__
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
#endif
int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <sleep_secs>\n", argv[0]); exit(1);
    }
    key_t semkey = 0x123456;
    int id = semget(semkey, 1, 0666);
    if(id==-1){     // 如果信号量集不存在，则新建
        printf("create semophore set\n");
        // 该信号量集中仅有一个信号量
        id = semget(semkey, 1, 0666|IPC_CREAT);
        if(id < 0){ perror("semget error"); exit(1); }
        // 初始化信号量集中的信号量(致命缺点，创建与初始化非原子操作)
        union semun u;
        u.val = 3;  // 指定该信号量集信号量的资源为3
        // 对 信号量0 进行设置
        if(semctl(id, 0, SETVAL, u) < 0){
            perror("semctl error"); exit(1);
        }
    }
    // p 表示获取操作，v 表示释放操作
    struct sembuf p = {0, -1, SEM_UNDO};  // 索引为0的信号量值减1
    struct sembuf v = {0, 1, SEM_UNDO};  // 索引为0的信号量值加1
    if(semop(id, &p, 1)<0){  // 参数2应该是一个数组，参数3应该是数组元素个数
        perror("semop error"); exit(1);
    }
    printf("%ld: %d P opt\n", time(NULL), getpid());
    sleep(atoi(argv[1]));
    printf("%ld: %d exit\n", time(NULL), getpid());
}

