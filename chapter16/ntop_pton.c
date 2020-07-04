// ntop_pton.c
#include <stdio.h>
#include <arpa/inet.h>

int main(){
    const char* str_ip = "192.168.1.189";
    char buf[INET_ADDRSTRLEN] = {0};
    struct in_addr addr;
    if(inet_pton(AF_INET, str_ip, &(addr.s_addr))!=1){
        fprintf(stderr, "inet_pton(%s) error\n", str_ip);
        return 1;
    }
    unsigned char* p = (unsigned char*)&(addr.s_addr);
    for(int i=0; i<4; ++i) printf("%u  ",  p[i]);
    printf("\n");
    if(NULL==inet_ntop(AF_INET, &addr, buf, INET_ADDRSTRLEN)){
        fprintf(stderr, "inet_pton error\n"); return 1;
    }
    printf("%s\n", buf);
}

