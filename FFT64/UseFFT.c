#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

int main(int argc, char **argv)
{

    while (1)
    {
        printf("Do yot want to calculate FFT64 ? [y/n]\n>");
        int num = 64, check_num;
        char cont, c, order;
        scanf("%s", &cont);
        if (cont != 'y')
        {
            printf("Exit the program\n");
            break;
        }
        Complex *test = malloc(sizeof(Complex) * num);
        printf("Do you want to get ordering 64-sequence by auto? [y/n]\n>");
        scanf("%s", &order);
        printf("%c", order);

        if (order == 'y')
        {

            num = 64;
            for (int i = 0; i < 32; i++)
            {
                test[i].Re = i;
                test[i + 1].Re = i;
            }
        }
        else if (order == 'n')
        {
            double real, imag;
            num = 64;

            for (int i = 0; i < num; ++i)
            {
                printf("Input the REAL part of [%d] : ", i);
                scanf("%lf", &real);
                c = getchar();
                test[i].Re = real;
                printf("Input the Imag part of [%d] : ", i);
                scanf("%lf", &imag);
                c = getchar();
                test[i].Im = imag;
            }
        }
        num = 64;
        printf("===========================================\n");
        printf("Before FFT\n");
        for (int i = 0; i < num; ++i)
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);

        FFT64(test);
        printf("===========================================\n");
        printf("After FFT\n");

        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        }
        // printf("===========================================\n");
        // IFFT32(test);
        // printf("After IFFT\n");
        // for (int i = 0; i < num; ++i)
        // {
        //     printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        // }
        printf("===========================================\n\n\n");
        free(test);
    }

    return 0;
}
