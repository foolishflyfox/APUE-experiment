// test-thread-process-shared.c
#include <unistd.h>
#include <stdio.h>

int main(){
#if defined(_POSIX_THREAD_PROCESS_SHARED)
    printf("_POSIX_THREAD_PROCESS_SHARED defined\n");
#else
    printf("_POSIX_THREAD_PROCESS_SHARED not defined\n");
#endif
    printf("sysconf(_SC_THREAD_PROCESS_SHARED) = %lu\n",
            sysconf(_SC_THREAD_PROCESS_SHARED));
}

