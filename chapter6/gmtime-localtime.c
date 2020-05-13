// gmtime-localtime.c
#include <stdio.h>
#include <time.h>

int main(){
    time_t t = time(NULL);
    struct tm* p = gmtime(&t);
    if(p==NULL){
        perror("gmtime error");
    }else{
        printf("   gmtime: %d-%d-%d %02d:%02d:%02d\n", p->tm_year+1900,
            p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    }
    if((p=localtime(&t))==NULL){
        perror("localtime error");
    }else{
        printf("localtime: %d-%d-%d %02d:%02d:%02d\n", p->tm_year+1900,
            p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    }
}
