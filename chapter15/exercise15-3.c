// exercise15-3.c
#include <stdio.h>

int main(){
    FILE *fp1 = popen("xyz", "r");
    if(fp1==NULL) perror("popen(\"xyz\", \"r\") error");
    else printf("fp1 = %p\n", fp1);
    FILE *fp2 = popen("xyz", "w");
    if(fp2==NULL) perror("popen(\"xyz\", \"w\") error");
    else printf("fp2 = %p\n", fp2);
}
