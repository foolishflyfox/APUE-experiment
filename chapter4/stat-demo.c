// file-type.c
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    struct stat buf;
    const char* str_type;
    for(int i=1; i<argc; ++i){
        if(stat(argv[i], &buf)==-1){
            str_type = "[ERROR] can't get file type.\n";
        }else{
            if(S_ISREG(buf.st_mode)){
                str_type = "regular";
            }else if(S_ISDIR(buf.st_mode)){
                str_type = "directory";
            }else if(S_ISCHR(buf.st_mode)){
                str_type = "character special";
            }else if(S_ISBLK(buf.st_mode)){
                str_type = "block special";
            }else if(S_ISFIFO(buf.st_mode)){
                str_type = "fifo";
            }else if(S_ISLNK(buf.st_mode)){
                str_type = "symbolic link";
            }else if(S_ISSOCK(buf.st_mode)){
                str_type = "socket";
            }else {
                str_type = "!!unknown mode!!";
            }
        }
        printf("%-12s : %s\n", argv[i], str_type);
    }
}

