#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"
#define PI 3.1415926535897932384

double Get_complex_square_value(Complex *c)
{
    return ((c->Re * c->Re) + (c->Im * c->Im));
}

void complex_add(Complex c1, Complex c2, Complex *c3)
{
    c3->Re = c1.Re + c2.Re;
    c3->Im = c1.Im + c2.Im;
}

void complex_sub(Complex c1, Complex c2, Complex *c3)
{
    c3->Re = c1.Re - c2.Re;
    c3->Im = c1.Im - c2.Im;
}

void complex_mul(Complex c1, Complex c2, Complex *c3)
{
    c3->Re = c1.Re * c2.Re - c1.Im * c2.Im;
    c3->Im = c1.Re * c2.Im + c1.Im * c2.Re;
}

void Get_Conjugate(int num, Complex *cinput, Complex *coutput)
{
    for (int i = 0; i < num; ++i)
    {
        coutput[i].Re = cinput[i].Re;
        coutput[i].Im = -cinput[i].Im;
    }
}
int index_reverse(int num, int index)
{
    int return_value = 0;
    for (int i = 0; i < num; ++i)
    {
        return_value |= (index >> ((num - 1) - i) & 1) << i;
    }
    return return_value;
}

void bit_reverse(int num, Complex *c)
{
    Complex temp;
    int reverse_index;
    int M = 0;
    int GetM = num;
    // 求 stage 也就是log2(Point個數)
    while (GetM != 1)
    {
        M++;
        GetM /= 2;
    }
    Complex copy[num];
    for (int i = 0; i < num; ++i)
    {
        copy[i] = c[i];
    }
    for (int i = 0; i < num; ++i)
    {
        reverse_index = index_reverse(M, i);
        c[i] = copy[reverse_index];
    }
}
void Wn_i(int n, int i, Complex *Wn, int flag)
{
    Wn->Re = cos(2 * PI * i / n);
    if (flag == 1)
        Wn->Im = -sin(2 * PI * i / n);
    else if (flag == 0)
        Wn->Im = -sin(2 * PI * i / n);
}

void DIT_FFT(int num, Complex *c)
{
    int M = 0, r, t, lc, m, i, l, la, lb, n;
    Complex wn, temp;
    // 求 stage 也就是log2(Point個數)
    int getM = num;
    while (getM != 1)
    {
        M++;
        getM /= 2;
    }
    // 做bit-reverse
    bit_reverse(num, c);

    for (m = 1; m <= M; m++)
    {
        la = pow(2, m);
        lb = la / 2;
        // printf("here %d, %d\n", la, lb);
        // butterfly calculate
        for (l = 1; l <= lb; l++)
        {
            // printf("%d\t", l);
            int r = (l - 1) * pow(2, M - m);
            for (n = l - 1; n < num - 1; n = n + la)
            {
                lc = n + lb;
                Wn_i(num, r, &wn, 1);
                complex_mul(c[lc], wn, &temp);
                complex_sub(c[n], temp, &(c[lc]));
                complex_add(c[n], temp, &(c[n]));
            }
        }
    }
}

void DIT_IFFT(int num, Complex *c)
{
    int i = 0;
    Get_Conjugate(num, c, c);
    DIT_FFT(num, c);
    Get_Conjugate(num, c, c);
    for (int i = 0; i < num; ++i)
    {
        c[i].Re /= num;
        c[i].Im /= num;
    }
}