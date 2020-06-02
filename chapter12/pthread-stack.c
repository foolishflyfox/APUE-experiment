// pthread-stack.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* foo(void* argv){
    int a = 10;
    printf("foo a = %p\n", &a);
    return NULL;
}
int main(){
    long thread_stack_min = sysconf(_SC_THREAD_STACK_MIN);
    int err;
    pthread_attr_t attr;
    printf("thread stack min : %ld\n", thread_stack_min);
    if((err=pthread_attr_init(&attr))!=0){
        fprintf(stderr, "pthread_attr_init error\n");
    }
    // 获取线程默认栈大小
    size_t stack_sz;
    void* stackaddr;
    err = pthread_attr_getstacksize(&attr, &stack_sz);
    if(err==0) printf("default stack size = %zu\n", stack_sz);
    else fprintf(stderr, "pthread_attr_getstacksize error\n");
    // 重新设置线程默认栈大小
    pthread_attr_setstacksize(&attr, stack_sz*2);
    // 获取线程默认地址和位置
    err = pthread_attr_getstack(&attr, &stackaddr, &stack_sz);
    if(err == 0) printf("now stack addr : %p, size = %zu\n", stackaddr, stack_sz);
    else fprintf(stderr, "pthread_attr_getstack error\n");
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err!=0) fprintf(stderr, "set detach state error\n");
    pthread_t tid;
    pthread_create(&tid, &attr, foo, NULL);
    sleep(1);
}
