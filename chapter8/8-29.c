// 8-29.c
#include <stdio.h>
#include <unistd.h>
#include <sys/acct.h>

#if defined(__linux__)
#define acct acct_v3
#endif

// #if !defined(HAS_ACORE)
// #define ACORE 0
// #endif
// #if !defined(HAS_AXSIG)
// #define AXSIG 0
// #endif

static unsigned long compt2ulong(comp_t comptime){
    unsigned long val;
    int exp;
    val = comptime & 0x1fff;
    exp = (comptime >> 13) & 7;
    while(exp-- > 0) val *= 8;
    return val;
}

int main(int argc, char* argv[]){
    struct acct acdata;
    FILE *fp;
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if(NULL==(fp=fopen(argv[1], "r"))){
        perror("fopen error"); return 1;
    }
    while(fread(&acdata, sizeof(acdata), 1, fp)==1){
        // acdata.ac_etime, acdata.ac_io
        printf("%10s: e = %6ld, chars = %7ld,  \n", acdata.ac_comm, 
            compt2ulong(acdata.ac_etime), compt2ulong(acdata.ac_io));
    }
    if(ferror(fp)) perror("read error");
}

