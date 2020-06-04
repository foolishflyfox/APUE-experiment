// pread-demo.c
#include <stdio.h>
#include <pthread.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int tmpfd;

void fun(int pos){
        for(int i=0; i<5000; ++i){
        char c; int ret;
#ifdef PREAD
        ret = pread(tmpfd, &c, 1, pos);
#else
        lseek(tmpfd, SEEK_SET, pos);
        ret = read(tmpfd, &c, 1);
#endif
        printf("%c\n", c);
    }
}

void* fa(void* arg){ fun(0); return NULL; }
void* fb(void* arg){ fun(1); return NULL; }

int main(){
    pthread_t ta, tb;
    if((tmpfd=open("tmp.txt", O_RDONLY))==-1){
        perror("open error"); return 1;
    }
    if(pthread_create(&ta, NULL, fa, NULL)){
        fprintf(stderr, "create fa thread error\n"); return 1;
    }
    if(pthread_create(&tb, NULL, fb, NULL)){
        fprintf(stderr, "create fb thread error\n"); return 1;
    }
    void* tret;
    if(pthread_join(ta, &tret)){
        fprintf(stderr, "join fa thread error\n"); return 1;
    }
    if(pthread_join(tb, &tret)){
        fprintf(stderr, "join fb thread error\n"); return 1;
    }
}
