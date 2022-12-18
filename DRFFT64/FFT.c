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

void FFT32(Complex *c)
{
    int num = 32;
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

void IFFT32(Complex *c)
{
    int num = 32;
    int i = 0;
    Get_Conjugate(num, c, c);
    FFT32(c);
    Get_Conjugate(num, c, c);
    for (int i = 0; i < num; ++i)
    {
        c[i].Re /= num;
        c[i].Im /= num;
    }
}

void FFT64(Complex *c)
{

    Complex *odd32 = malloc(sizeof(Complex) * 32);
    Complex *even32 = malloc(sizeof(Complex) * 32);
    for (int i = 0; i < 64; i = i + 2)
    {
        even32[i / 2] = c[i];
        odd32[i / 2] = c[i + 1];
    }
    FFT32(even32);
    FFT32(odd32);

    // for (int i = 0; i < 32; ++i)
    // {
    //     printf("Odd : [%d] \t%lf\t%lf\n", i, odd32[i].Re, odd32[i].Im);
    // }
    // for (int i = 0; i < 32; ++i)
    // {
    //     printf("Even : [%d] \t%lf\t%lf\n", i, even32[i].Re, even32[i].Im);
    // }
    Complex *Wn = malloc(sizeof(Complex) * 64);
    Complex temp, t;
    for (int i = 0; i < 64; ++i)
    {
        Wn[i].Re = cos(2 * PI * i / 64);
        Wn[i].Im = -sin(2 * PI * i / 64);
    }
    // for (int i = 0; i < 64; ++i)
    // {
    //     printf("Wn : [%d] \t%lf\t%lf\n", i, Wn[i].Re, Wn[i].Im);
    // }
    for (int i = 0; i < 64; ++i)
    {

        complex_mul(Wn[i], odd32[i % 32], &temp);
        complex_add(even32[i % 32], temp, &temp);
        c[i] = temp;
        // printf("%d\t%lf\t%lf\n", i, c[i].Re, c[i].Im);
    }
}

void reverse(Complex *c)
{
    int num = 64;
    Complex *temp = malloc(sizeof(Complex) * num);
    for (int i = 0; i < 64; ++i)
    {
        temp[i] = c[i];
    }
    for (int i = 0; i < 64; ++i)
    {
        c[i] = temp[63 - i];
    }
}

void IFFT64(Complex *c)
{
    int num = 64;
    int i = 0;
    Get_Conjugate(num, c, c);
    FFT64(c);
    Get_Conjugate(num, c, c);
    for (int i = 0; i < num; ++i)
    {
        c[i].Re /= num;
        c[i].Im /= num;
    }
}

void DRFFT64(Complex *c1, Complex *c2)
{
    Complex *total = malloc(sizeof(Complex) * 64);
    for (int i = 0; i < 64; i++)
    {
        total[i].Re = c1[i].Re;
        total[i].Im = c2[i].Im;
    }
    FFT64(total);
    Complex *total_reverse = malloc(sizeof(Complex) * 64);
    for (int i = 0; i < 64; ++i)
    {
        total_reverse[i].Re = total[i].Re;
        total_reverse[i].Im = total[i].Im;
    }
    // printf("Here n\n");
    // for (int i = 0; i < 64; i++)
    // {
    //     printf("[%d]\t%lf\t%lf\n", i, total_reverse[i].Re, total_reverse[i].Im);
    // }
    reverse(total_reverse);
    // printf("Here -n\n");
    // for (int i = 0; i < 64; i++)
    // {
    //     printf("[%d]\t%lf\t%lf\n", i, total_reverse[i].Re, total_reverse[i].Im);
    // }
    Complex *total_reverse_conj = malloc(sizeof(Complex) * 64);
    for (int i = 0; i < 64; ++i)
    {
        total_reverse_conj[(i + 1) % 64] = total_reverse[i];
    }
    // printf("Here -n+1\n");
    // for (int i = 0; i < 64; i++)
    // {
    //     printf("[%d]\t%lf\t%lf\n", i, total_reverse_conj[i].Re, total_reverse_conj[i].Im);
    // }
    Get_Conjugate(64, total_reverse_conj, total_reverse_conj);
    for (int i = 0; i < 64; ++i)
    {
        printf("total[%d]\t%lf\t%lf\t", i, total[i].Re, total[i].Im);
        printf("total_reverse_conj[%d]\t%lf\t%lf\n", i, total_reverse_conj[i].Re, total_reverse_conj[i].Im);
        c1[i].Re = (total[i].Re + total_reverse_conj[i].Re) / 2;
        c1[i].Im = (total[i].Im + total_reverse_conj[i].Im) / 2;
        c2[i].Re = (-total[i].Re - total_reverse_conj[i].Re) / 2;
        c2[i].Im = (-total[i].Im - total_reverse_conj[i].Im) / 2;
    }
}