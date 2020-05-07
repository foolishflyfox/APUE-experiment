// error-demo.c
#include <assert.h>

#if (N<5)
    #error N is smaller than 5
#endif

int main(){
    assert(N>10);
}
