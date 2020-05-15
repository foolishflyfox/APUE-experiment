// getrlimit-demo.c
#include <sys/resource.h>
#include <stdio.h>

static void pr_limits(const char *name, int resource){
    struct rlimit limit;
    if(getrlimit(resource, &limit)<0){
        fprintf(stderr, "getrlimit error for %s", name);
        return;
    }
    printf("%-14s ", name);
    if(limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)  ");
    }else{
        printf("%10lld  ", (long long)limit.rlim_cur);
    }
    if(limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)\n");
    }else{
        printf("%10lld\n", (long long)limit.rlim_max);
    }
}
#define doit(name) pr_limits(#name, name)

int main(void){

#ifdef RLIMIT_AS
    doit(RLIMIT_AS);
#endif
    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);
#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif
#ifdef RLIMIT_MSGQUEUE
    doit(RLIMIT_MSGQUEUE);
#endif
#ifdef RLIMIT_NICE
    doit(RLIMIT_NICE);
#endif
    doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPROC
    doit(RLIMIT_NPROC);
#endif
#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif
#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif
#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif
#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif
    doit(RLIMIT_STACK);
#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP);
#endif
#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif
}

