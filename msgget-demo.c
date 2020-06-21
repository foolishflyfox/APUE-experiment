// msgget-demo.c
#include <stdio.h>
#include <sys/msg.h>
#include <pwd.h>
#include <grp.h>

int main(){
    key_t key = 0x6667;
    int msgid = msgget(key, IPC_CREAT|0644);
    if(msgid == -1) {
        perror("msgget error"); return 1;
    }else{
        struct msqid_ds buf;
        if(msgctl(msgid, IPC_STAT, &buf)==-1){
            perror("msgctl(IPC_STAT) error"); return 1;
        }else{
            printf("ID=%d, key=0x%x, mode=0%o, owner=%s, group=%s\n", msgid, 
                key, buf.msg_perm.mode, getpwuid(buf.msg_perm.uid)->pw_name,
                getgrgid(buf.msg_perm.gid)->gr_name);
        }
    }
}
