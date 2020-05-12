// getprotobyname-demo.c
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <protocol>\n", argv[0]); return 1;
    }
    struct protoent* p_protoent = getprotobyname(argv[1]);
    if(p_protoent!=NULL){
        printf("%s codename is %d\n", argv[1], p_protoent->p_proto);
    }
}
