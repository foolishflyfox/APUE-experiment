// flags.c
#include <stdio.h>

int main(){
    printf("%'d\n", 1234567);  // '貌似没效果
    printf("|%5d|\n", 12);     // 输出: |   12|
    printf("|%-5d|\n", 12);    // 输出: |12   |
    printf("|%+5d|\n", 12);    // 输出: |  +12|
    printf("|%05d|\n", 12);    // 输出: |00012|
    printf("|% d|\n", 12);     // 输出: | 12|
    printf("%#x\n", 1234);     // 输出: 0x4d2
    printf("%#X\n", 1234);     // 输出: 0X4D2
    printf("%x\n", 1234);      // 输出: 4d2
}
