#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int num = 0;
    int odd = 0;
    int even = 0;
    while (1 == 1) {
        scanf("%d", &num);
        if (num == 0) {
            break;
        } else if (num == 13) {
            scanf("%d", &num);
        } else if (num % 2 == 0) {
            even = even + num;
        } else {
            odd = odd + num;
        }
        printf("%d, %d\n", odd, even);
    }
    printf("%d", even - odd);
}
