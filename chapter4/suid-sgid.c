// suid-sgid.c
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    struct stat buf;
    if(stat(argv[1], &buf)==-1){
        printf("ERROR: Can't get %s stat.\n", argv[1]);
    }else{
        printf("set-user-ID: %s\n",buf.st_mode&S_ISUID ?"true":"false");
        printf("set-group-ID: %s\n",buf.st_mode&S_ISGID ?"true":"false");
    }
}


