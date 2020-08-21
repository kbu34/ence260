#include <stdio.h>

void smoothData(int n, double data[])
{
    double holder = 0.0;
    double holder2 = 0.0;

    holder = ((data[0] * 3) + data[1]) / 4;
    for (int i = 1; i < n - 1; i++) {
        holder2 = (data[i - 1] + (2 * data[i]) + data[i + 1]) / 4;
        data[i - 1] = holder;
        holder = holder2;
    }
    data[n - 1] = (data[n - 2] + (3 * data[n - 1])) / 4;
    data[n - 2] = holder;
}

int main(void) 
{
	double data[] = {0.0, 9.809999, 9.809999, 9.809999, 0.0, 0.0, 0.0, 9.82, 9.82, 9.82, 5.0, 5.0, 5.0, 9.82, 9.82, 9.82, 4.99, 4.99, 4.99, 9.80, 9.82, 10.0};
	smoothData(23, data);
	printf("Smoothed data: %.2lf", data[0]);
	for (int i = 1; i < 22; i++) {
		printf(", %.2lf", data[i]);
	}
	puts("");
}
