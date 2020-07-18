// 17-12.c
#include <string.h>
#include <unistd.h>

int send_fd(int fd, int fd_to_send);
/*
 * Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead. We send the error back
 * using the send_fd() protocol.
 */
int send_err(int fd, int errcode, const char *msg){
    int     n = strlen(msg);
    if (n > 0){
        int nleft = n, nwritten;
        const char* ptr = msg;
        while(nleft > 0) {
            if((nwritten = write(fd, ptr, nleft)) < 0){
                if(nleft==n) return -1;
                else break;
            }else if(nwritten==0)
                break;
            nleft -= nwritten;
            ptr += nwritten;
        }
        if(n-nleft!=n) return -1;
    }
    if(errcode >=0 ) errcode = -1;  /* must be negative */
    if(send_fd(fd, errcode) < 0) return -1;
    return 0;
}

