// strftime-demo.c
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <format>\n", argv[0]);
        return 1;
    }
    const int bufsize = 128;
    time_t t = time(NULL);
    char buf[bufsize];
    if(strftime(buf, bufsize, argv[1], localtime(&t))==0){
        fputs("buffer length 128 is too small\n", stderr);
    }else{
        printf("%s\n", buf);
    }
}
