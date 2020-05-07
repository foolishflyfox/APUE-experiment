#include <stdio.h>
#include <sys/stat.h>

void pr_stdio(const char* name, FILE* fp);
int is_unbuffered(FILE* fp);
int is_linebuffered(FILE* fp);
int buffer_size(FILE* fp);

int main(){
    FILE *fp;
    // 在 stdout/stdin/stderr 中传入数据，缓冲区才会被开辟
    fputs("enter any character\n", stdout);
    if(getchar()==EOF) perror("getchar error");
    fputs("one line to standard error\n", stderr);
    pr_stdio("stdin", stdin);
    pr_stdio("stdout", stdout);
    pr_stdio("stderr", stderr);
    
    if((fp=fopen("/etc/passwd", "r"))==NULL){
        perror("open /etc/passwd error");
    }else{
        if(getc(fp)==EOF) perror("getc error");
        pr_stdio("/etc/passwd", fp);
    }
    struct stat buf;
    if(stat("/etc/passwd", &buf)==-1) perror("stat error");
    printf("st_blksize = %d\n", (int)buf.st_blksize);
}

void pr_stdio(const char* name, FILE* fp){
    printf("stream = %s, ", name);
    if(is_unbuffered(fp)) printf("unbuffered");
    else if(is_linebuffered(fp)) printf("line buffered");
    else printf("fully buffered");
    printf(", buffer size = %d\n", buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)
    int is_unbuffered(FILE* fp){
        return (fp->_flags & _IO_UNBUFFERED);
    }
    int is_linebuffered(FILE* fp){
        return (fp->_flags & _IO_LINE_BUF);
    }
    int buffer_size(FILE* fp){
        return (fp->_IO_buf_end - fp->_IO_buf_base);
    }
#elif defined (__SNBF)
    int is_unbuffered(FILE *fp){
        return (fp->_flags & __SNBF);
    }
    int is_linebuffered(FILE* fp){
        return (fp->_flags & __SLBF);
    }
    int buffer_size(FILE* fp){
        return (fp->_bf._size);
    }
#else
    #error unknow stdio implementation!
#endif
