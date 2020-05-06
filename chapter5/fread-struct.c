// fread-struct.c
#include <stdio.h>
struct {
    short count;
    long total;
    char name[64];
}item;

int main(){
    FILE* fp = fopen("tmp", "r");
    if(fp==NULL){
        perror("fopen error"); return 1;
    }
    if(fread(&item, sizeof(item), 1, fp)<1){
        perror("fread error"); return 1;
    }
    printf("%d, %ld, %s\n", item.count, item.total, item.name);
}

