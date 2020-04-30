// calc-sum.c
#include <stdio.h>
int main(){
    double sum = 0, v;
    int r;
    while(r=scanf("%lf", &v), r!=0 && r!=EOF)
        sum += v;
    printf("sum = %lf\n", sum);
}
