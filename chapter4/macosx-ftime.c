// macosx-ftime.c
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>

const char* get_stime(struct timespec ts){
    static char strbuf[64];
    bzero(strbuf, 64);
    struct tm* stm = localtime(&ts.tv_sec);
    sprintf(strbuf, "%d-%02d-%02d %02d:%02d:%02d.%ld",
                1900+stm->tm_year, stm->tm_mon+1, stm->tm_mday,
                stm->tm_hour, stm->tm_min, stm->tm_sec, ts.tv_nsec);
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
        printf("mtime %s\n", get_stime(buf.st_mtimespec));
        printf("ctime: %s\n", get_stime(buf.st_ctimespec));
        printf("atime: %s\n", get_stime(buf.st_atimespec));
    }
}
