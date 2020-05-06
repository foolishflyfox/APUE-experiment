// fwrite-struct.c
#include <stdio.h>
struct {
    short count;
    long total;
    char name[64];
}item;

int main(){
    FILE* fp = fopen("tmp", "w");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    item.count = 10; 
    item.total = 123;
    sprintf(item.name, "%s", "foolishflyfox");
    if(fwrite(&item, sizeof(item), 1, fp)<1){
        perror("fwrite error"); return 1;
    }
}

