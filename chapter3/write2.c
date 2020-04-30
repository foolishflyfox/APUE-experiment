// write2.c
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    const char* fn = "out.data";
    int loop_times = 50000;
    pid_t son_pid;
    if((son_pid = fork())!=0){
        // parent process
        int fd = open(fn, O_WRONLY|O_CREAT, 0644);
        while(loop_times-- > 0){
            lseek(fd, 0, SEEK_END); write(fd, "a", 1);
        }
        close(fd);
    }else{
        // son process
        int fd = open(fn, O_WRONLY|O_CREAT, 0644);
        while(loop_times-- > 0){
            lseek(fd, 0, SEEK_END); write(fd, "b", 1);
        }
        close(fd);
        return 0;
    }
    waitpid(son_pid, NULL, 0);
    return 0;
}

