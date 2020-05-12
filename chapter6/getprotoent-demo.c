// getprotoent-demo.c
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <protocol>\n", argv[0]); return 1;
    }
    struct protoent* p_protoent;
    int proto_no = -1;
    while((p_protoent = getprotoent())!=NULL){
        if(strcmp(p_protoent->p_name, argv[1])==0){
            proto_no = p_protoent->p_proto;
        }
    }
    if(proto_no!=-1){
        printf("%s codename is %d\n", argv[1], proto_no);
    }
}
