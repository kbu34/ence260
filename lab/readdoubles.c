#include <stdio.h>

int readDoubles(int n, double data[])
{
    /* read double numbers from stdin into array until EOF */
    int read = 0;
    double num = 0.0;
    double check = 0.0;

    check = scanf("%lf", &num);
    while (read < n && check != EOF) {
        data[read] = num;
        read++;
        check = scanf("%lf", &num);
    }
    return read;
}

int main(void)
{
	double data[5] = {0.0};
	int numRead = 0;

	numRead = readDoubles(4, data);
	printf("Read %d values:\n", numRead);
	for (int i = 0; i < numRead; i++) {
		printf("%0.3lf\n", data[i]);
	}	
}
