// device-no.c
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#ifdef __APPLE__
#include <sys/types.h>
#endif
#ifdef __linux__
#include <sys/sysmacros.h>
#endif

int main(int argc, char* argv[]){
    if(argc == 1){
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }
    struct stat buf;
    for(int i=1; i<argc; ++i){
        if(stat(argv[i], &buf)==-1){
            fprintf(stderr, "can't get %s state: %s\n", 
                        argv[i], strerror(errno));
        }else{
            int dev_maj=major(buf.st_dev), dev_min=minor(buf.st_dev);
            int rdev_maj=major(buf.st_rdev), rdev_min=minor(buf.st_rdev);
            printf("%s: dev = %d/%d  ", argv[i], dev_maj, dev_min);
            if(S_ISCHR(buf.st_mode)){
                printf("(character) rdev = %d/%d", rdev_maj,rdev_min);
            }else if(S_ISBLK(buf.st_mode)){
                printf("(block) rdev = %d/%d", rdev_maj,rdev_min);
            }
            printf("\n");
        }
    }
}
