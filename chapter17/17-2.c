// 17-2.c
#include <sys/socket.h>
/*
 * Returns a full-duplex pipe (a UNIX domain socket) wit
 * the two file descriptors returned in fd[0] and fd[1].
 */
int fd_pipe(int fd[2]){
    return socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
}

