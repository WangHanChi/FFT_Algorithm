#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

int main(int argc, char **argv)
{

    while (1)
    {
        printf("Do yot want to calculate FFT ? [y/n]\n>");
        int num = 20, check_num;
        char cont, c, order;
        scanf("%s", &cont);
        if (cont != 'y')
        {
            printf("Exit the program\n");
            break;
        }
        Complex *test = malloc(sizeof(Complex) * num);
        printf("Do you want to get ordering sequence by auto? [y/n]\n>");
        scanf("%s", &order);
        printf("%c", order);
        // c = getchar();

        if (order == 'y')
        {
            printf("Please Enter the Point numbers you want?\n>");
            scanf("%d", &num);
            c = getchar();
            check_num = num;
            while ((check_num & (check_num - 1)))
            {
                check_num++;
            }
            if (num != check_num)
            {
                printf("The number you input is not 2^n , so I fill it to satisfy 2^n\nthe num will be %d\n\n", check_num);
                num = check_num;
            }

            for (int i = 0; i < num; i++)
            {
                // test[i].Re = 63 - i;
                test[i].Re = i;
            }
        }
        else if (order == 'n')
        {
            double real, imag;
            printf("Please Enter the Point numbers you want?\n>");
            scanf("%d", &num);
            c = getchar();
            check_num = num;
            while ((check_num & (check_num - 1)))
            {
                check_num++;
            }
            if (num != check_num)
            {
                printf("The number you input is not 2^n , so I fill it to satisfy 2^n\nthe num will be %d", check_num);
                num = check_num;
            }

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

        // printf("Please Enter the Point numbers you want?\n>");
        // scanf("%d", &num);
        // check_num = num;
        // while ((check_num & (check_num - 1)))
        // {
        //     check_num++;
        // }
        // num = check_num;

        // for (int i = 0; i < num; i++)
        // {
        //     test[i].Re = i;
        // }
        printf("===========================================\n");
        printf("Before FFT\n");
        for (int i = 0; i < num; ++i)
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);

        DIT_FFT(num, test);
        printf("===========================================\n");
        printf("After FFT\n");

        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        }
        printf("===========================================\n");
        DIT_IFFT(num, test);
        printf("After IFFT\n");
        for (int i = 0; i < num; ++i)
        {
            printf("[ %d ]\t%lf\t%lf\n", i, test[i].Re, test[i].Im);
        }
        printf("===========================================\n\n\n");
        free(test);
    }

    return 0;
}
