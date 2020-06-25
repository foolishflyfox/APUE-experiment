// msgrcv-demo.c
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long mtype;
    char mtext[512];
}msgbuf;

int main(int argc, char* argv[]){
    int msg_type = 0;
    if(argc > 1) msg_type = atoi(argv[1]);
    key_t key = 0x6667;
    int msgid = msgget(key, 0);
    if(msgid == -1) { perror("msgget error"); exit(1); }
    msgbuf buf;
    if(-1==msgrcv(msgid, &buf, sizeof(buf), msg_type, 0)){
        perror("msgrcv error"); exit(1);
    }else{
        printf("%s\n", buf.mtext);
    }
    exit(0);
}

