// 16-10.c
#include <sys/socket.h>
#include <unistd.h>

#define MAXSLEEP 128

int connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen){
    int numsec;
    /* Try to connect with exponential backoff */
    for(numsec = 1; numsec <= MAXSLEEP; numsec <<= 1){
        if(connect(sockfd, addr, alen) == 0){
            /* Connection accepted. */
            return 0;
        }
        if(numsec <= MAXSLEEP/2)
            sleep(numsec);
    }
    return -1;
}
