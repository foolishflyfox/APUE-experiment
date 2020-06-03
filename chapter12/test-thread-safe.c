// test-thread-safe.c
#include <stdio.h>
#include <unistd.h>

int main(){
#ifdef _POSIX_THREAD_SAFE_FUNCTIONS
    printf("support thread save\n");
#else
    printf("not support thread save\n");
#endif
    printf("sysconf(_SC_THREAD_SAFE_FUNCTIONS) = %ld\n", 
            sysconf(_SC_THREAD_SAFE_FUNCTIONS));
}
