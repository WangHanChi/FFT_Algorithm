#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"
#define PI 3.1415926

double Get_complex_square_value(Complex *c)
{
    return ((c->Re * c->Re) + (c->Im * c->Im));
}

void complex_add(Complex *c1, Complex *c2, Complex *c3)
{
    c3->Re = c1->Re + c2->Re;
    c3->Im = c1->Im + c2->Im;
}

void complex_sub(Complex *c1, Complex *c2, Complex *c3)
{
    c3->Re = c1->Re - c2->Re;
    c3->Im = c1->Im - c2->Im;
}

void complex_mul(Complex *c1, Complex *c2, Complex *c3)
{
    c3->Re = c1->Re * c2->Re;
    c3->Im = c1->Im * c2->Im;
}

void complex_div(Complex *c1, Complex *c2, Complex *c3)
{
    c3->Re = c1->Re / c2->Re;
    c3->Im = c1->Im / c2->Im;
}

void Get_Conjugate(int num, Complex *cinput, Complex *coutput)
{
    for (int i = 0; i < num; ++i)
    {
        coutput[i].Re = cinput[i].Re;
        coutput[i].Im = -cinput[i].Im;
    }
}
void bit_reverse(int num, Complex *c)
{
    int M = 0;
    while (num != 1)
    {
        M++;
        num /= 2;
    }
}

void DIT_FFT(int num, Complex *c)
{
    Complex *temp, Wn;
    int M = 0;

    // 求 stage 也就是log2(Point個數)
    while (num != 1)
    {
        M++;
        num /= 2;
    }
}