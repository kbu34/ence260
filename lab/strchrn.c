#include <stdio.h>
#include <stdlib.h>

char* strchrn(char* s, int c, int n)
{
    char* ptr = NULL;
    int found = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            found++;
            if (found == n) {
                ptr = &s[i];
            }
        }
    }
    return ptr;
}

int main(void) 
{
    char* line = "This is a string";
    for (int n = 1; n <= 5; n++) {
        char* ptr = strchrn(line, 'i', n);
        if (ptr != NULL) {
            int index = ptr - line;
            printf("Occurrence %d of 'i' found at index = %d\n", n, index);
        } else {
             printf("Occurrence %d of 'i' not found\n", n);
        }
    }
}
