// stdio-type.c
#include <stdio.h>

int main(){
#if defined(_IO_UNBUFFERED)
    printf("_IO_LINE_BUF = %d\n", _IO_LINE_BUF);
	printf("_IO_UNBUFFERED = %d\n", _IO_UNBUFFERED);
#elif defined(__SNBF)
    printf("__SLBF = %d\n", __SLBF);
	printf("__SNBF = %d\n", __SNBF);
#endif
}




