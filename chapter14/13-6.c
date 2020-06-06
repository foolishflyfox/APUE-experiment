// 13-6.c
#include <unistd.h>
#include <fcntl.h>

int lockfile(int fd){
    struct flock fl;
    fl.l_type = F_RDLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return (fcntl(fd, F_SETLK, &fl));
}
