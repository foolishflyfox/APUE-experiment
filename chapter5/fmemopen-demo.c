// fmemopen-demo.c
#include <stdio.h>
#include <string.h>

#define BSZ 48

int main(){
    FILE* fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    if((fp=fmemopen(buf, BSZ, "w+"))==NULL){
        perror("fmemopen failed"); return 1;
    }
    // 以 fmemopen w+ 方式打开后，buf[0] = '\0'
    printf("initial buffer contents: %s, %c\n", buf, buf[1]);
    fprintf(fp, "hello, world");
    printf("before fflush: %s\n", buf);
    fflush(fp);
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));
}

