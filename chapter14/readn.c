// readn.c
#include <sys/types.h>
#include <unistd.h>

ssize_t readn(int fd, void *ptr, size_t n){
    size_t nleft = n;
    ssize_t n_read;
    while (nleft > 0) {
        if((n_read = read(fd, ptr, nleft)) < 0){
            if(nleft == n) return -1;  /* error, return -1 */
            else break;  /* error, return amount read so far */
        }else if(n_read == 0){
            break;  /* EOF */
        }
        nleft -= n_read;
        ptr += n_read;
    }
    return n-nleft; /* return >= 0 */
}

