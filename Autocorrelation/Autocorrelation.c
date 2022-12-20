#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

#define NUM 32

void auto_direct(double *, double *);

int main(int argc, char **argv)
{
    printf("DSP Program HW2-1\n\n(a)\n");
    printf("A direct real autocorrecttion computation program\n\n");
    double *auto_out = malloc(sizeof(double) * 64);
    double *x = malloc(sizeof(double) * 33);
    for (int i = 1; i < 33; i++)
    {
        x[i] = i % 2 ? i : -i;
    }
    x[0] = 0;
    auto_direct(auto_out, x);
    for (int i = 0; i < 64; i++)
    {
        printf("R[%3d]\t:%lf\n", i - 32, auto_out[i]);
    }

    printf("A direct real autocorrecttion computation program\n\n");
    return 0;
}

void auto_direct(double *R, double *x)
{
    for (int i = -31; i <= 31; i++)
    {
        double sum = 0;
        for (int j = 1; j <= 32; j++)
        {
            if (j + i < 1 || j + i > 33)
                continue;
            sum += x[j] * x[(j + i)];
        }
        R[i + 32] = sum;
    }
}
