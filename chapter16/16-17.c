// 16-17.c
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFLEN  128
#define QLEN    10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

int initserver(int type, const struct sockaddr* addr, 
  socklen_t alen, int qlen){
    int fd, err = 0;
    if((fd = socket(addr->sa_family, type, 0)) < 0) return 1;
    if(bind(fd, addr, alen) < 0) goto errout;
    if(type == SOCK_STREAM || type == SOCK_DGRAM) 
        if(listen(fd, qlen) < 0) goto errout;
    return fd;
errout:
    err = errno; close(fd); errno = err; return -1;
}
int set_cloexec(int fd){
    int val = fcntl(fd, F_GETFD, 0);
    if(val < 0) return -1;
    val |= FD_CLOEXEC;
    return fcntl(fd, F_SETFD, val);
}
void daemonize(const char *cmd){
    int             i, fd0, fd1, fd2;
    pid_t           pid;
    struct rlimit   rl;
    struct sigaction sa;
    umask(0);       // clear file creation mask
    // get maximum number of file descriptors.
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0){
        fprintf(stderr, "%s: can't get file limit\n", cmd);
        exit(1);
    }
    // Become a session leader to lose controlling TTY
    if((pid = fork()) < 0){
        perror("1 fork error"); exit(1);
    } else if(pid != 0) /* parent */
        exit(0);
    setsid();
    /* Ensure future opens won't allocate controlling TTYs */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0){
        perror("can't ignore SIGHUP"); exit(1);
    }
    if((pid = fork()) < 0){
        perror("2 fork error"); exit(1);
    }else if(pid!=0) /* parent */
        exit(0);
    if(chdir("/") < 0){
        perror("can't change directory to /"); exit(1);
    }
    // close all open file descriptors
    if(rl.rlim_max == RLIM_INFINITY) rl.rlim_max = 1024;
    for( i = 0; i < rl.rlim_max; ++i) close(i);
    // attach file descriptors 0, 1, and 2 to /dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if(fd0!=0 || fd1!=1 || fd2!=2){
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
            fd0, fd1, fd2);
        exit(1);
    }
}

void serve(int sockfd){
    int     clfd;
    FILE    *fp;
    char    buf[BUFLEN];
    set_cloexec(sockfd);
    for( ; ;){
        if((clfd = accept(sockfd, NULL, NULL)) < 0){
            fprintf(stderr, "ruptimed: accept error: %s\n", strerror(errno));
            exit(1);
        }
        set_cloexec(clfd);
        if((fp = popen("/usr/bin/uptime", "r"))==NULL){
            sprintf(buf, "error: %s\n", strerror(errno));
            send(clfd, buf, strlen(buf), 0);
        } else {
            while(fgets(buf, BUFLEN, fp) != NULL)
                send(clfd, buf, strlen(buf), 0);
            pclose(fp);
        }
        close(clfd);
    }
}
int main(int argc, char *argv[]){
    struct  addrinfo *ailist, *aip;
    struct  addrinfo hint;
    int     sockfd, err, n;
    char    *host;
    if(argc != 1) {
        fprintf(stderr, "usage: ruptimed\n"); exit(1);
    }
    if((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
        n = HOST_NAME_MAX;  /*best guess*/
    if((host = malloc(n)) == NULL){
        perror("malloc error"); exit(1);
    }
    if(gethostname(host, n) < 0){
        perror("gethostname error"); exit(1);
    }
    daemonize("ruptimed");  // 守护进程化
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if((err = getaddrinfo(host, "ruptime", &hint, &ailist))!=0){
        syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s", 
            gai_strerror(err));
        exit(1);
    }
    for(aip = ailist; aip != NULL; aip = aip->ai_next){
        if((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
            aip->ai_addrlen, QLEN)) >= 0){
            serve(sockfd);  exit(0);
        }
    }
    exit(1);
}


