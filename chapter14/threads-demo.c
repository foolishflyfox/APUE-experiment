// threads-demo.c
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#define BUFSIZE 511
char buf1[BUFSIZE+1], buf2[BUFSIZE+1];
void* thr_fn(void* arg){
    int fd2 = open("t2.pip", O_RDONLY), n2;
    if(fd2==-1) { perror("open t2.pip error"); return NULL; }
    while((n2 = read(fd2, buf2, BUFSIZE)) > 0){
        buf2[n2] = '\0';
        printf("%ld<t2.pip>:  %s\n", time(NULL), buf2);
    }
    return NULL;
}
int main(){
    pthread_t tid; void* tret;
    if(pthread_create(&tid, NULL, thr_fn, NULL)!=0){
        fprintf(stderr, "pthread_create error\n"); return 1;
    }
    int fd1 = open("t1.pip", O_RDONLY), n1;
    if(fd1==-1) { perror("open t1.pip error"); return 1; }
    while((n1 = read(fd1, buf1, BUFSIZE)) > 0){
        buf1[n1] = '\0';
        printf("%ld<t1.pip>:  %s\n", time(NULL), buf1);
    }
    if(pthread_join(tid, &tret)!=0) fprintf(stderr, "pthread_join error\n");
}
