// hostent-demo.c
#include <stdio.h>
#include <netdb.h>

int main(){
    struct hostent* ent = gethostent();
    if(ent==NULL) { perror("gethostent error"); return 1; }
    printf("h_name = \"%s\"\n", ent->h_name);
    for(int i=0; ent->h_aliases[i]!=NULL; ++i){
        printf("h_aliases[%d] = \"%s\"\n", i, ent->h_aliases[i]);
    }
    switch(ent->h_addrtype){
        case AF_INET: printf("h_addrtype = AF_INET\n"); break;
        case AF_INET6: printf("h_addrtype = AF_INET6\n"); break;
    }
    printf("h_length = %d\n", ent->h_length);
    for(int i=0; ent->h_addr_list[i]!=NULL; ++i){
        printf("h_addr_list[%d] = \"%s\"\n", i, ent->h_addr_list[i]);
    }
}

