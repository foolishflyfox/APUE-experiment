// msgsnd-demo.c
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long mtype;
    char mtext[512];
}msgbuf;

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "Usage: %s <type> <msg>\n", argv[0]); exit(1);
    }
    key_t key = 0x6667;
    int msgid = msgget(key, 0);
    if(msgid == -1) {
        perror("msgget error"); exit(1);
    }
    msgbuf buf;
    buf.mtype = atol(argv[1]);
    strncpy(buf.mtext, argv[2], 512);
    if(-1==msgsnd(msgid, &buf, strlen(argv[2])+1, 0)){
        perror("msgsnd error"); exit(1);
    }
}
