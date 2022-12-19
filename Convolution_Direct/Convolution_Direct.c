#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

#define NUM 32
double *Convolution_Direct(double *, double *);
double *Convolution_DFRRT64(double *, double *);

int main(int argc, char **argv)
{
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
    double *new_x = malloc(sizeof(double) * 64);
    double *new_y = malloc(sizeof(double) * 64);
    double *out2;

    free(out);
    return 0;
}

double *Convolution_DFRRT64(double *new_x, double *new_y)
{
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
    return out;
}