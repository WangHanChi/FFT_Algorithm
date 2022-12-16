#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

int main(int argc, char **argv)
{

    while (1)
    {
        printf("Do yot want to calculate FFT ? [y/n]\n>");
        int num, check_num;
        char cont, c;
        scanf("%c", &cont);
        if (cont != 'y')
        {
            printf("Exit the program\n");
            break;
        }

        printf("Please Enter the Point numbers you want?\n>");
        scanf("%d", &num);
        check_num = num;
        while ((check_num & (check_num - 1)))
        {
            check_num++;
        }
        num = check_num;
        Complex *test = malloc(sizeof(Complex) * num);
        for (int i = 0; i < num; i++)
        {
            test[i].Re = i;
        }
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
        while ((c = getchar()) != EOF && c != '\n')
            ;
    }

    return 0;
}
