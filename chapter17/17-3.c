// 17-3.c
#include <poll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NQ      3       /* number of queue */
#define MAXMSG  512     /* maximum message size */
#define KEY     0x123   /* key for first message queue */

struct threadinfo{
    int qid;
    int fd;
};
struct mymesg{
    long mtype;
    char mtext[MAXMSG];
};
void *helper(void *arg){
    int                 n;
    struct mymesg       m;
    struct threadinfo   *tip = arg;
    for( ; ;) {
        memset(&m, 0, sizeof(m));
        if((n = msgrcv(tip->qid, &m, MAXMSG, 0, MSG_NOERROR)) < 0){
            perror("msgrcv error"); exit(1);
        }
        if(write(tip->fd, m.mtext, n) < 0){
            perror("write error"); exit(1);
        }
    }
}

int main(){
    int                 i, n, err;
    int                 fd[2];
    int                 qid[NQ];
    struct pollfd       pfd[NQ];
    struct threadinfo   ti[NQ];
    pthread_t           tid[NQ];
    char                buf[MAXMSG];

    for(i = 0; i < NQ; i++){
        if((qid[i] = msgget((KEY+i), IPC_CREAT|0666)) < 0){
            perror("msgget error"); exit(1);
        }
        printf("queue ID %d is %d\n", i, qid[i]);
        if(socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0){
            perror("socketpair error"); exit(1);
        }
        pfd[i].fd = fd[0];
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];
        if((err = pthread_create(&tid[i], NULL, helper, &ti[i]))!=0){
            perror("pthread_create error"); exit(1);
        }
    }
    for( ; ; ){
        if(poll(pfd, NQ, -1) < 0){
            perror("poll error"); exit(1);
        }
        for(i=0; i<NQ; i++){
            if(pfd[i].revents & POLLIN){
                if((n = read(pfd[i].fd, buf, sizeof(buf))) < 0){
                    perror("read error"); exit(1);
                }
                buf[n] = 0;
                printf("queue id %d, message %s\n", qid[i], buf);
            }
        }
    }
}

