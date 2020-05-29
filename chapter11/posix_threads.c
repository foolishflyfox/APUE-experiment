// posix_threads.c
#include <stdio.h>
#include <unistd.h>

int main(){
#ifdef _POSIX_THREADS
    printf("_POSIX_THREADS = %ld\n", _POSIX_THREADS);
#else
    printf("No _POSIX_THREADS\n");
#endif
    printf("sysconf(_SC_THREADS) = %ld\n", sysconf(_SC_THREADS));
}
