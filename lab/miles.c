#include <stdio.h>

#include <stdlib.h>

#define KILO 1.609344

int main(void)
{
    float miles = 0;
    float kilometers = 0;
    printf("How many miles? ");
    scanf("%f", &miles);
    kilometers = miles * KILO;
    printf("That's %.2f km.", kilometers);
    return 0;
}
