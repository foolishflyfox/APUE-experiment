// mktime-demo.c
#include <stdio.h>
#include <time.h>

int main(){
    time_t t1 = time(NULL);
    struct tm* p = localtime(&t1);
    time_t t2 = mktime(p);
    printf("t1 = %ld\nt2 = %ld\n", t1, t2);
}
