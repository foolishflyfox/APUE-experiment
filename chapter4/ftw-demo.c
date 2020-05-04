// ftw-demo.c
#include <ftw.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static int nreg = 0;
static int nblk = 0;
static int nchr = 0;
static int ndir = 0;
static int nfifo = 0;
static int nslink = 0;
static int nsock = 0;

int fn(const char* path, const struct stat* ptr, int flag){
    int cnt = 0;
    const char* filename = path;
    for(const char* pt = path; *pt; ++pt){
        if(*pt=='/'){
            filename = pt+1;
            if(cnt) printf("    ");
            ++cnt;
        }
    }
    if(cnt) printf("└── ");
    printf("%s", filename);
    // 添加文件类型 可执行文件:* , 符号链接:@, 文件夹:/, 套接字:=
    // 管道:|, 块设备:#, 字符设备:%
    switch(flag){
        case FTW_F:
            switch(ptr->st_mode & S_IFMT){
                case S_IFREG:
                    nreg++;
                    if(ptr->st_mode&S_IEXEC)printf("*");
                    break;
                case S_IFBLK: nblk++; printf("#"); break;
                case S_IFCHR: nchr++; printf("%%"); break;
                case S_IFDIR: perror("FTW_F is dir"); break;
                case S_IFIFO: nfifo++; printf("|"); break;
                case S_IFSOCK: nsock++; printf("="); break;
            }
            break;
        case FTW_D: ndir++; printf("/"); break;
        #ifdef __APPLE__
        case FTW_SLN: 
        #endif
        case FTW_SL: nslink++; printf("@"); break;
        default: 
            printf(" [Unknow file type: %s]", path);
        break;
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[]){
    if(argc!=2){
        fprintf(stderr, "Usage: %s <dir-path>\n", argv[0]);
        return 1;
    }
    nreg = nblk = nchr = ndir = nfifo = nslink = nsock = 0;
    if(ftw(argv[1], fn, 1)<0){
        perror("ftw error"); return 1;
    }else{
        int nfiles = nreg+nblk+nchr+nfifo+nslink+nsock;
        printf("\n%d directories, %d files\n", ndir-1, nfiles);
    }
}

