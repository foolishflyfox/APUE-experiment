// pagesize.c
#include <unistd.h>
#include <stdio.h>

void showvar(const char* name, int val) { printf("%s = %d\n", name, val); }
#define SHOWVAR(var) showvar(#var, var)
int main(){
    SHOWVAR(sysconf(_SC_PAGESIZE));
    SHOWVAR(sysconf(_SC_PAGE_SIZE));
}
