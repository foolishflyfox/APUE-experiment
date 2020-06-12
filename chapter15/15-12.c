// 15-12.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
/* Pointer to array allocated at run-time. */
static pid_t *childpid = NULL;
/* From our open_max(), {Figure 2.17} */
static int maxfd;
FILE* Popen(const char *cmdstring, const char *type){
    int pfd[2];
    pid_t pid;
    FILE *fp;
    if((type[0]!='r' && type[0]!='w') || type[1]!='\0' ){
        errno = EINVAL; return NULL;
    }
    if(pipe(pfd) < 0) { perror("pipe error"); exit(1); }
    if(childpid == NULL) {  /* first time through */
        /* allocate zeroed out array for child pids */
        maxfd = sysconf(_SC_OPEN_MAX); // 简单起见没有调用 open_max
        if((childpid = calloc(maxfd, sizeof(pid_t))) == NULL)
            return NULL;
    }
    if (pipe(pfd) < 0) return NULL;  /* errno set by pipe() */
    if (pfd[0] >= maxfd || pfd[1] >= maxfd){
        close(pfd[0]);
        close(pfd[1]);
        errno = EMFILE;
        return NULL;
    }
    if((pid = fork()) < 0) return NULL;  /* errno set by fork() */
    else if(pid == 0){  /* child */
        if(*type == 'r'){
            close(pfd[0]);
            if(pfd[1]!=STDOUT_FILENO){
                dup2(pfd[1], STDOUT_FILENO);
                close(pfd[1]);
            }
        } else {
            close(pfd[1]);
            if(pfd[0]!=STDIN_FILENO){
                dup2(pfd[0], STDIN_FILENO);
                close(pfd[0]);
            }
        }
        /* close all descriptors in childpid */
        for(int i=0; i<maxfd; ++i){
            if(childpid[i] > 0)
                close(i);
        }
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        _exit(127);
    }
    /* parent continue... */
    if(*type == 'r'){
        close(pfd[1]);
        if((fp = fdopen(pfd[0], type))==NULL) return NULL;
    }else{
        close(pfd[0]);
        if((fp = fdopen(pfd[1], type))==NULL) return NULL;
    }
    childpid[fileno(fp)] = pid;  /* remember child pid for this fd */
    return fp;
}
int Pclose(FILE *fp){
    int fd, stat;
    pid_t pid;
    if(childpid == NULL) {
        errno = EINVAL; return -1; /* popen() has never been called */
    }
    fd = fileno(fp);
    if(fd >= maxfd) {
        errno = EINVAL; return -1; /* invalid file descriptor */
    }
    if((pid = childpid[fd])==0){
        errno = EINVAL; return -1; /* fp wasn't opened by popen */
    }
    childpid[fd] = 0;
    if(fclose(fp)==EOF) return -1;
    while(waitpid(pid, &stat, 0) < 0)
        if(errno != EINTR)
            return -1;  /* error other than EINTER from waitpid() */
    return stat;
}
#define MAXLINE 1024
#define  DEF_PAGER "${PAGER:-more}"  /* environment variable, or default */
int main(int argc, char* argv[]){
    char line[MAXLINE];
    FILE *fpin, *fpout;
    if(argc!=2){fprintf(stderr, "Usage: %s <pathname>\n", argv[0]); exit(1);}
    if((fpin = fopen(argv[1], "r")) == NULL){perror("fopen error"); exit(1);}
    if((fpout = Popen(DEF_PAGER, "w")) == NULL){perror("Popen error"); exit(1);}
    while(fgets(line, MAXLINE, fpin) != NULL){
        if(fputs(line, fpout) == EOF){perror("fputs error to pipe"); exit(1);}
    }
    if(ferror(fpin)) { perror("fgets error"); exit(1);}
    if(Pclose(fpout) == -1){ perror("Pclose error"); exit(1);}
}
