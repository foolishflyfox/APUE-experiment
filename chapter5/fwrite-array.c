// fwrite-array.c
#include <stdio.h>

int main(){
    FILE* fp = fopen("tmp", "w");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    float data[10] = {0, 1.1, 3.1416, 0.618, 2.718};
    if(fwrite(data+2, sizeof(float), 4, fp)!=4){
        perror("fwrite error"); return 1;
    }
}
