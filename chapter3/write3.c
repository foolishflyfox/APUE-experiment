// write3.c
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    const char* fn = "out.data";
    int loop_times = 50000;
    int fd = open(fn, O_WRONLY|O_CREAT, 0644);
    pid_t son_pid;
    if((son_pid = fork())!=0){
        // parent process
        while(loop_times-- > 0) write(fd, "a", 1);
    }else{
        // son process
        while(loop_times-- > 0) write(fd, "b", 1);
        return 0;
    }
    waitpid(son_pid, NULL, 0);
    close(fd);
    return 0;
}

