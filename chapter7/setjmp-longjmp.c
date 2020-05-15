// setjmp-longjmp.c
#include <stdio.h>
#include <limits.h>
#include <setjmp.h>

#define MAXLINE 1024
#define TOK_ADD 1
#define TOK_SUB 2

jmp_buf jmpbuffer;

char *tok_ptr;
int g_val = 0;

int get_token(void){
    // 获取 tok_ptr 的下一个命令
    while(*tok_ptr==' '||*tok_ptr=='\t'||*tok_ptr=='\n') ++tok_ptr;
    if(*tok_ptr=='\0') return -1;
    if(*tok_ptr=='+') {tok_ptr++; return TOK_ADD;}
    if(*tok_ptr=='-') {tok_ptr++; return TOK_SUB;}
    int token = INT_MIN;
    tok_ptr += sscanf(tok_ptr, "%d", &token);
    return token;
}
void cmd_add(void){
    int token = get_token();
    if(token==INT_MIN) longjmp(jmpbuffer, 1);
    g_val += token;
}
void cmd_sub(void){
    int token = get_token();
    if(token==INT_MIN) longjmp(jmpbuffer, 2);
    g_val -= token;
}

void do_line(char* ptr){
    int cmd;
    tok_ptr = ptr;
    g_val = 0;
    while((cmd=get_token())>0){
        switch(cmd){
            case TOK_ADD:
                cmd_add();
                break;
            case TOK_SUB:
                cmd_sub();
                break;
        }
    }
    printf("%d\n", g_val);
}
int main(){
    char line[MAXLINE];
    switch(setjmp(jmpbuffer)){
        case 1: fputs("cmd_add error\n", stderr); break;
        case 2: fputs("cmd_sub error\n", stderr); break;
    }
    if(fgets(line, MAXLINE, stdin)!=NULL) do_line(line);
}
