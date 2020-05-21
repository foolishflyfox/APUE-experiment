// errno-demo.c
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

void openfile(const char* filename){
    if(open(filename, O_RDONLY)==-1){
        printf("open %s fail, errno = %d\n", filename, errno);
    }else{
        printf("open %s success, errno = %d\n", filename, errno);
    }
}

int main(){
	printf("origin errno: %d\n", errno);
#ifdef ERR
	openfile("abcd");
#endif
	openfile("/dev/null");
}



