// semaphore-demo.c
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    const char *semname = "helloworld";
    if(argc!=2){
        fprintf(stderr, "Usage: %s <sleep_secs>\n", argv[0]); exit(1);
    }
    sem_t *semp = sem_open(semname, O_CREAT, 0666, 3);
    if(SEM_FAILED == semp){ perror("sem_open error"); exit(1); }

    if(sem_wait(semp)==-1) { perror("sem_wait error"); exit(1); }
    printf("%ld: %d P opt (sem_wait)\n", time(NULL), getpid());
    sleep(atoi(argv[1]));
    if(sem_post(semp)==-1) { perror("sem_post error"); exit(1); }
    printf("%ld: %d V opt (sem_post)\n", time(NULL), getpid());

    if(sem_close(semp)==-1){ perror("sem_close error"); exit(1); }
}

