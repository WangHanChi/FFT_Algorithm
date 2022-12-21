#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

#define NUM 32
double *Convolution_Direct(double *, double *);
Complex *Convolution_DFRRT64(Complex *, Complex *);

int main(int argc, char **argv)
{
    printf("DSP Program HW2-1\n\n");
    printf("(a) a direct real convolution program\n\n");
    double *x = malloc(sizeof(double) * NUM);
    double *h = malloc(sizeof(double) * NUM);
    double *out;

    for (int i = 0; i < NUM; i++)
    {
        x[i] = 3 * (i + 1);
        h[i] = NUM - 2 * (i + 1);
    }
    out = Convolution_Direct(x, h);

    for (int i = 0; i < NUM * 2 - 1; i++)
    {
        printf("out[%d] : %lf\n", i, out[i]);
    }

    printf("==========================================\n");

    printf("(b) a real convolution program by calling DRFFT64(x, y) once\n\n");
    Complex *new_x = malloc(sizeof(Complex) * 64);
    Complex *new_y = malloc(sizeof(Complex) * 64);
    Complex *out2;
    for (int i = 0; i < NUM; i++)
    {
        new_x[i].Re = 3 * (i + 1);
        new_y[i].Re = NUM - 2 * (i + 1);
    }
    out2 = Convolution_DFRRT64(new_x, new_y);
    for (int i = 0; i < NUM * 2 - 1; i++)
    {
        printf("out2[ %d ]:\t %lf     \t%lf\n", i, out2[i].Re, out2[i].Im);
    }
    free(out2);
    free(out);
    return 0;
}

Complex *Convolution_DFRRT64(Complex *new_x, Complex *new_y)
{
    new_x = realloc(new_x, sizeof(Complex) * 64);
    new_y = realloc(new_y, sizeof(Complex) * 64);
    for (int i = 32; i < 64; i++)
    {
        new_x[i].Re = new_x[i].Im = new_y[i].Re = new_y[i].Im = 0;
    }
    DRFFT64(new_x, new_y);
    Complex *out = malloc(sizeof(Complex) * 64);
    Complex temp;
    for (int i = 0; i < 64; i++)
    {
        complex_mul(new_x[i], new_y[i], &temp);
        out[i] = temp;
    }
    IFFT64(out);
    free(new_y);
    free(new_x);
    return out;
}

double *Convolution_Direct(double *x, double *h)
{
    int m = NUM, n = NUM;
    double *out = malloc(sizeof(double) * (NUM * 2 - 1));
    x = realloc(x, sizeof(double) * 64);
    h = realloc(h, sizeof(double) * 64);

    if (!x || !h)
    {
        printf("Error\n");
        free(x);
        free(h);
        return NULL;
    }

    // realloc and set data
    for (int i = m; i < n + m; i++)
    {
        x[i] = h[i] = 0;
    }

    for (int i = 0; i < n + m - 1; ++i)
    {
        out[i] = 0;
        for (int j = 0; j < m; j++)
        {
            if (i - j + 1 > 0)
                out[i] = out[i] + x[j] * h[i - j];
        }
    }
    free(h);
    free(x);
    return out;
}
