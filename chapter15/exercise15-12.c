// exercise15-12.c
#include <stdio.h>
#include <sys/msg.h>
typedef struct {
    long mtype;
    char mtext[512];
}msgbuf;
int main(){
    key_t key = 0x11111;
    struct msqid_ds buf;
    msgbuf mb = {11111, "abc"};
    for(int i=0; i<5; ++i){
        int msgid = msgget(key, IPC_CREAT|0644);
        if(msgid==-1) { perror("1 msgget error"); return 1; }
        else{
            mb.mtype = 11101;
            if(-1 == msgsnd(msgid, &mb, 3, 0)){
                perror("1 msgsnd error"); return 1;
            }
            if(msgctl(msgid, IPC_RMID, 0)==-1){
                perror("msgctl(IPC_RMID) error"); return 1;
            }
        }
    }
    for(int i=0; i<5; ++i){
        int msgid = msgget(IPC_PRIVATE, IPC_CREAT|0666);
        if(msgid==-1) { perror("2 msgget error"); return 1; }
        if(-1 == msgsnd(msgid, &mb, 3, 0)){
            perror("msgsnd error"); return 1;
        }
    }
}
