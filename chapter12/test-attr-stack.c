// test-attr-stack.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(){
#if defined(_POSIX_THREAD_ATTR_STACKADDR) || defined(_POSIX_THREAD_ATTR_STACKSIZE)
    printf("Your OS supports thread stack\n");
#else
    printf("Your OS does't support thread stack\n");
#endif
}

