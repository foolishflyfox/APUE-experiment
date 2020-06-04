// pthread-key-max.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void show(const char* name, int var){printf("%s = %d\n", name, var);}
#define SHOW(VAR) show(#VAR, VAR)

int main(){
#ifdef _POSIX_THREAD_KEYS_MAX
    SHOW(_POSIX_THREAD_KEYS_MAX);
#endif
#ifdef _SC_THREAD_KEYS_MAX
    SHOW(sysconf(_SC_THREAD_KEYS_MAX));
#endif
}
