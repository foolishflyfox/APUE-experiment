// strptime-demo.c
#include <stdio.h>
#include <time.h>

int main(){
    struct tm t;
    strptime("2020-5-13 16:58:00", "%F %T", &t);
    printf("year: %d\n", t.tm_year);
    printf("month: %d\n", t.tm_mon);
    printf("day: %d\n", t.tm_mday);
    printf("hour: %d\n", t.tm_hour);
    printf("minute: %d\n", t.tm_min);
    printf("second: %d\n", t.tm_sec);
}
