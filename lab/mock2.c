#include <stdio.h>

typedef struct info_s Address;

struct info_s{
    char streetname[50];
    int number;
    char unit;
};

int main(void)
{
    Address home = {"Baker Street", 221, 'B'};
    printf("The name's Sherlock Holmes, and the address is %d-%c %s.\n", home.number, home.unit, home.streetname);
}
