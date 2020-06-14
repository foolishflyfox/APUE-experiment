// prog1.c
#include <stdio.h>
#define BSZ 1024
int main(){
    char buf[BSZ];
    while(fgets(buf, BSZ, stdin)!=NULL){
        for(char* p = buf; *p!='\0'; ++p) 
            if(*p<='z'&&*p>='a')
                *p = *p-'a'+'A';
        printf("%s", buf);
    }
    if(ferror(stdin)) { perror("fgets error"); return 1; }
}
