// time-clock.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#define SHOWVAR(var) showvar(#var, var)

void showvar(const char* varname, long v){
    printf("%s = %ld\n", varname, v);
}

int main(){
    SHOWVAR((long)sizeof(clock_t));
    SHOWVAR((long)sizeof(time_t));
    long clk_tck = sysconf(_SC_CLK_TCK);
    SHOWVAR(clk_tck);
    struct tms buf;
    time_t t0 = time(NULL);
    clock_t c0 = times(&buf);
    printf("t0 = %ld, c0 = %ld, ", t0, c0);
    SHOWVAR( t0 * clk_tck );
    sleep(3);
    time_t t1 = time(NULL);
    clock_t c1 = times(&buf);
    printf("t1 = %ld, c1 = %ld, ", t1, c1);
    SHOWVAR( t1 * clk_tck );
    long dt = t1 - t0, dc = c1 - c0;
    printf("dt = %ld, dc = %ld, ", dt, dc);
    SHOWVAR( dt * clk_tck );
}
