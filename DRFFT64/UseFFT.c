#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

int main(int argc, char **argv)
{

    while (1)
    {
        printf("Do yot want to calculate DRFFT64 ? [y/n]\n>");
        int num = 64, check_num;
        char cont, c, order;
        scanf("%s", &cont);
        if (cont != 'y')
        {
            printf("Exit the program\n");
            break;
        }
        Complex *test = malloc(sizeof(Complex) * num);
        Complex *test2 = malloc(sizeof(Complex) * num);
        printf("Do you want to get ordering 64-sequence by auto? [y/n]\n>");
        scanf("%s", &order);
        printf("%c", order);

        if (order == 'y')
        {

            num = 64;
            for (int i = 0; i < 64; i++)
            {
                test[i].Re = i;
                test2[i].Re = 63 - i;
            }
        }
        else if (order == 'n')
        {
            double real, imag;
            num = 64;
            printf("A sequence : \n");
            for (int i = 0; i < num; ++i)
            {
                printf("Input the REAL part of A[%d] : ", i);
                scanf("%lf", &real);
                c = getchar();
                test[i].Re = real;
                printf("Input the Imag part of A[%d] : ", i);
                scanf("%lf", &imag);
                c = getchar();
                test[i].Im = imag;
            }
            printf("B sequence : \n");
            for (int i = 0; i < num; ++i)
            {
                printf("Input the REAL part of B[%d] : ", i);
                scanf("%lf", &real);
                c = getchar();
                test2[i].Re = real;
                printf("Input the Imag part of B[%d] : ", i);
                scanf("%lf", &imag);
                c = getchar();
                test2[i].Im = imag;
            }
        }
        num = 64;
        printf("===========================================\n");
        printf("Before DRFFT64\n");

        printf("This is A sequence : \n");
        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        }
        printf("This is B sequence : \n");
        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test2[i].Re, test2[i].Im);
        }

        DRFFT64(test, test2);
        printf("===========================================\n");
        printf("After DRFFT64\n");
        printf("This is A sequence : \n");
        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        }
        printf("This is B sequence : \n");
        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test2[i].Re, test2[i].Im);
        }
        // printf("===========================================\n");
        // IFFT64(test);
        // printf("After IFFT64\n");
        // for (int i = 0; i < num; ++i)
        // {
        //     printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        // }
        printf("===========================================\n\n\n");
        free(test);
    }

    return 0;
}
