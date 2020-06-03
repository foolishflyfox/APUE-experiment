// 12-6a.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct{ 
    const char* msg;
    const char* next_msg;
}A;
void* func2(void* argv){
    A* x = argv;
    if(x->next_msg!=NULL) x->msg = x->next_msg;
    printf("%lu: func2, %s\n", time(NULL), x->msg);
    return NULL;
}
void* func1(void* argv){
    A* x = argv;
    printf("%lu: func1 start\n", time(NULL));
    x->msg = "from func1";
    func2(argv);
    sleep(1);
    func2(argv);
    printf("%lu: func1 end\n", time(NULL));
    return NULL;
}
int main(){
    A x; x.msg = "init"; x.next_msg = NULL;
    func1(&x);
    x.next_msg = "world";
    func2(&x);
}

