// getgrgid-demo.c
#include <stdio.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/types.h>
#include <stdlib.h>

void show_group_entry(struct group* p_grp){
    printf("Gid: %u\n", p_grp->gr_gid);
    printf("Group name: %s\n", p_grp->gr_name);
    printf("Group passwd: %s\n", p_grp->gr_passwd);
    printf("Members:\n");
    for(char** pp = p_grp->gr_mem; *pp!=NULL; pp++){
        printf("    %s\n", *pp);
    }
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <gid>\n", argv[0]); return 1;
    }
    gid_t gid = atoi(argv[1]);
    struct group* p_grp;
    if((p_grp=getgrgid(gid))==NULL){
        fprintf(stderr, "no gid equal to %s\n", argv[1]); return 1;
    }
    show_group_entry(p_grp);
}
