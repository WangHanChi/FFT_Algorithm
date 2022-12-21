#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

#define NUM 32

void auto_direct(double *, double *);
void auto_DRFFT64(Complex *, Complex *);


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
    printf("\n\n(b)\n");
    printf("A direct real autocorrecttion computation program\n\n");

    Complex *x2 = malloc(sizeof(Complex) * 32);
    Complex *auto_out2 = calloc(sizeof(Complex), 64);
    for (int i = 0; i < 32; i++)
    {
        x2[i].Re = (i + 1) % 2 ? -(i + 1) : (i + 1);
    }
    x[0] = 0;
    auto_DRFFT64(auto_out2, x2);
    for (int i = 0; i < 64 - 1; i++)
    {
        printf("R[%3d]\t:%lf\n", i - 31, auto_out2[i].Re);
    }
    return 0;
}

void auto_DRFFT64(Complex *R, Complex *x)
{
    x = realloc(x, sizeof(Complex) * 64);
    for (int i = 32; i < 64; i++)
    {
        x[i].Re = 0;
        x[i].Im = 0;
    }
    Complex *h = calloc(sizeof(Complex), 64);
    for (int i = 0; i < 32; i++)
        h[i].Re = x[31 - i].Re;

    DRFFT64(x, h);

    // Complex *result = calloc(sizeof(Complex), 64);

    for (int i = 0; i < 64; i++)
    {
        complex_mul(x[i], h[i], &R[i]);
    }

    IFFT64(R);

    // for (int i = 0; i < 64; i++)
    // {
    //     printf("out2[ %d ]:\t %lf     \t%lf\n", i, result[i].Re, result[i].Im);
    // }

    // double sum = 0;
    // for (int k = 0; k < 64; k++)
    // {
    // }
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
