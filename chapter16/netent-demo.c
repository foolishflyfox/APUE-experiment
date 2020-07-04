// netent-demo.c
#include <netdb.h>
#include <stdio.h>

int main(){
    struct netent* ent = getnetent();
    if(ent==NULL){ perror("getnetbyname error"); return 1; }
    printf("n_name = \"%s\"\n", ent->n_name);
    for(int i=0; ent->n_aliases[i]!=NULL; ++i)
        printf("n_aliases[%d] = \"%s\"\n", i, ent->n_aliases[i]);
    switch(ent->n_addrtype){
        case AF_INET: printf("n_addrtype = AF_INET\n"); break;
        case AF_INET6: printf("n_addrtype = AF_INET6\n"); break;
    }
    printf("n_net = %d\n", ent->n_net);
}
