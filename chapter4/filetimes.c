// filetimes.c
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>

const char* get_stime(time_t secs){
    static char strbuf[64];
    bzero(strbuf, 64);
    struct tm* stm = localtime(&secs);
    sprintf(strbuf, "%d-%02d-%02d %02d:%02d:%02d",
                1900+stm->tm_year, stm->tm_mon+1, stm->tm_mday,
                stm->tm_hour, stm->tm_min, stm->tm_sec);
    return strbuf;
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    struct stat buf;
    if(stat(argv[1], &buf)==-1){
        perror("stat error");
        return 1;
    }else{
        // modify, change state, access
        printf("mtime %s, ", get_stime(buf.st_mtime));
        printf("ctime: %s, ", get_stime(buf.st_ctime));
        printf("atime: %s\n", get_stime(buf.st_atime));
    }
}
