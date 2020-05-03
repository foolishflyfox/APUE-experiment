// utimes-demo.c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#ifdef __linux__
#include <time.h>
#endif

int get_timeval(const char* str_tm, struct timespec* tmv){
    int year, mon, day, hour, min, sec, ns=0;
    int inputs = sscanf(str_tm, "%d-%d-%d %d:%d:%d.%d", 
                &year, &mon, &day, &hour, &min, &sec, &ns);
    struct tm s_tm;
    if(inputs==1){
        if(year==0){
            tmv->tv_nsec = UTIME_NOW;
        }else if(year==-1){
            tmv->tv_nsec = UTIME_OMIT;
        }else{
            return -1;
        }
    }else if(inputs<6){
        return -1;
    }else{
        s_tm.tm_year = year - 1900;
        s_tm.tm_mon = mon - 1;
        s_tm.tm_mday = day;
        s_tm.tm_hour = hour;
        s_tm.tm_min = min;
        s_tm.tm_sec = sec;
        tmv->tv_sec = timelocal(&s_tm);
        tmv->tv_nsec = ns;
        int i = 1000000000;
        while(ns>0)ns /= 10, i /=10;
        tmv->tv_nsec *= i;
    }
    return 0;
}

int main(int argc, char* argv[]){
    const char* usage = "Usage: %s <path> <access-time> <modify-time>\n\
access-time and modify-time can be:\n\t-1 - ignore\n\t0 - current time\n\
\t\"YYYY-MM-DD HH:MM:SS.us\" \n\
example:\n\t%s filename \"2020-5-3 14:11:52.32\" -1 \n";
    if(argc!=4){
        fprintf(stderr, usage, argv[0], argv[0]);
        return 1;
    }
    struct timespec times[2];
    if(get_timeval(argv[2], times)==-1){
        fprintf(stderr, "time \"%s\" is wrong\n", argv[2]);
        return 1;
    }
    if(get_timeval(argv[3], &(times[1]))==-1){
        fprintf(stderr, "time \"%s\" is wrong\n", argv[3]);
        return 1;
    }
    if(utimensat(AT_FDCWD, argv[1], times, AT_SYMLINK_NOFOLLOW)==-1){
        perror("utimensat error");
        return 1;
    }
    return 0;
}

