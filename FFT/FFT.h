#ifndef __FFT_H__
#define __FFT_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double Re;
    double Im;

} Complex;

double Get_complex_square_value(Complex *c); // get the complex square value
void complex_add(Complex, Complex, Complex *);
void complex_sub(Complex, Complex, Complex *);
void complex_mul(Complex, Complex, Complex *);
void DIT_FFT(int num, Complex *);
void Get_Conjugate(int num, Complex *, Complex *);
int index_reverse(int num, int bit);
void bit_reverse(int num, Complex *c);
void Wn_i(int n, int i, Complex *Wn, int flag);
void DIT_IFFT(int num, Complex *c);
#endif // end define FFT.h