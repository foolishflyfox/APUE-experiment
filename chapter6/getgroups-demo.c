// getgroups-demo.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

int main(){
    gid_t gids[32];
    int cnt = 0;
    if((cnt=getgroups(sizeof(gids)/sizeof(gid_t), gids))==-1){
        perror("getgroups error"); return 1;
    }
    printf("%s in %d groups: ", getpwuid(getuid())->pw_name, cnt);
    for(int i=0; i<cnt; ++i){
        printf("%s%c", getgrgid(gids[i])->gr_name, ", "[i==cnt-1]);
    }
    putchar('\n');
}
