#include <stdio.h>

int tokenCopy(char* dest, const char* src, int destSize)
{
    int copied = 0;
    int end = 0;

    while (*src != 0 && copied < destSize - 1 && *src != 32) {
        *dest = *src;
        src++;
        dest++;
        copied++;
    }
    end = copied;
    while (end < destSize) {
        *dest = 0;
        end++;
    }
    return copied;
}

int main(void)
{
    char buff[5];
    int n = tokenCopy(buff, "This is a string", 5);
    printf("%d '%s'\n", n, buff);
}
