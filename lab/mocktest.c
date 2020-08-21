#include <stdio.h>

void swap3(int* x, int* y, int* z)
{
    int i = 0;
    if (*z > *y) {
        i = *z;
        *z = *y;
        *y = i;
    }
    if (*y > *x) {
        i = *y;
        *y = *x;
        *x = i;
    }
}

int main(void) 
{
    int a = -101;
    int b = -421;
    int c = -1;
    swap3(&a, &b, &c);
    printf("%d <= %d <= %d\n", c, b, a);
}
