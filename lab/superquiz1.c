/* Author: Phillip Kim
 * Date 8/8/19
 * 
 * This program reads double values from a file and puts them in an array,
 * then smooths out the data, then prints out the times the critical 
 * values have been exceeded as well as the peak data. */

#include <stdio.h>
#define CRITICAL_HIGH 9.81
#define CRITICAL_LOW 5.0

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
    data[read + 1] = -1.0;
    return read;
}

void smoothData(int n, double data[])
{
    /* smooths out the data witout creating a new array */
    double holder = 0.0;
    double holder2 = 0.0;
    int i = 0;

    holder = ((data[0] * 3) + data[1]) / 4;
    for (i = 1; i < n - 1 && data[i + 1] != -1.0; i++) {
        holder2 = (data[i - 1] + (2 * data[i]) + data[i + 1]) / 4;
        data[i - 1] = holder;
        holder = holder2;
    }
    data[i - 1] = (data[i - 2] + (3 * data[i - 1])) / 4;
    data[i + 1] = 0.0;
}

int main(void)
{
    /* reads data, then smooth the data, then finds the times the critical 
     * values have been exceeded */
    double data[100000] = {0.0};
    double time = 0.0;
    double max = 0.0;
    double max_time = 0.0;
    int exceeded = 0;
    
    readDoubles(100000, data);
    smoothData(100000, data);
    max = data[0];
    for (int i = 0; i < 100000; i++) {
        if (max < data[i]) {
            max = data[i];
            max_time = time;
        }
        if (data[i] > CRITICAL_HIGH && exceeded == 0) {
            printf("Acceleration of %.2lf m/sec^2 exceeded at t = %.2lf secs.\n", CRITICAL_HIGH, time);
            exceeded = 1;
        } else if (data[i] < CRITICAL_LOW && exceeded == 1) {
            exceeded = 0;
        }
        time = time + 0.01;
    }
    printf("\nMaximum acceleration: %.2lf m/sec^2 at t = %.2lf secs.\n", max, max_time);
}
