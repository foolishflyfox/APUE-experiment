#include "apue.h"

void err_doit(const char* fmt, va_list ap){
    char buf[MAXLINE+1];
    vsnprintf(buf, MAXLINE, fmt, ap);
    int slen = strlen(buf);
    if(slen>0 && slen<MAXLINE && buf[slen-1]!='\n'){
        buf[slen] = '\n';
        buf[slen+1] = 0;
    }
    fputs(buf, stderr);
}
void err_quit(const char* fmt, ...){
    fputs("\033[35mUSER ERROR:\033[0m ", stderr);
    va_list ap;
    // va_start 只能出现在带有省略号参数的函数中
    va_start(ap, fmt);
    err_doit(fmt, ap);
    va_end(ap);
    exit(1);
}
void err_sys(const char* fmt, ...){
    fputs("\033[31mSYSTEM ERROR:\033[0m ", stderr);
    if(errno){
        fprintf(stderr, "[%d: %s] ", errno, strerror(errno));
    }
    va_list ap;
    va_start(ap, fmt);
    err_doit(fmt, ap);
    va_end(ap);
    exit(1);
}

