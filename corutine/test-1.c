// test-1.c
#include <stdio.h>

void consume(int number){
    static int state = 0;
    switch(state){
        case 0:
            printf("enter consume\n");
            state++;
            while(1){
                printf("consumer: Get %d\n", number);
                return;
        case 1: continue;
            }
    }
}
int main(){
    for(int i=0; i<3; ++i) {
        printf("Create %d\n", i);
        consume(i);
    }
}

