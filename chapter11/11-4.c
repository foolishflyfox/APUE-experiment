// 11-4.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct foo{
    int a, b, c, d;
};
void printfoo(const char* s, const struct foo* fp){
    printf("%s", s);
    printf("  structure at 0x%lx\n", (unsigned long)fp);
    printf("  foo.a = %d\n", fp->a);
    printf("  foo.b = %d\n", fp->b);
    printf("  foo.c = %d\n", fp->c);
    printf("  foo.c = %d\n", fp->c);
}
void* thr_fn1(void* arg){
    struct foo foo = {1, 2, 3, 4};
    printfoo("thread 1:", &foo);
    pthread_exit(&foo);
}
void* thr_fn2(void* arg){
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}
int main(){
    int err;
    pthread_t tid1, tid2;
    struct foo* fp;
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if(err!=0){
        fprintf(stderr, "error %d: can't create thread 1\n", err);
        return 1;
    }
    err = pthread_join(tid1, (void**)&fp);
    if(err!=0){
        fprintf(stderr, "error %d: can't join with thread 1\n", err);
        return 1;
    }
    sleep(1);
    printf("parent starting second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if(err!=0){
        fprintf(stderr, "error %d: can't create thread 2\n", err);
        return 1;
    }
    sleep(1);
    printfoo("parent: \n", fp);
}

