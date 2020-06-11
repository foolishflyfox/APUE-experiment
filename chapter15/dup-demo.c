#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define BSZ 255
void* thrfn(void* fd_ptr){
	int n,  fd = *(int*)fd_ptr;
	char buf[BSZ+1];
	while( (n = read(fd, buf, BSZ)) > 0 ){
		buf[n] = '\0';
		printf("sub thread: %s", buf);
	}
	return NULL;
}

int main(){
	int n, fd = dup(STDIN_FILENO);
	if(fd==-1) {perror("dup error"); exit(1); }
	pthread_t tid;
	if(pthread_create(&tid, NULL, thrfn, &fd)) {
		perror("pthread_create error"); exit(1);
	}
	char buf[BSZ+1];
	while( (n = read(STDIN_FILENO, buf, BSZ)) > 0 ){
		buf[n] = '\0';
		printf("main thread: %s", buf);
	}
}


