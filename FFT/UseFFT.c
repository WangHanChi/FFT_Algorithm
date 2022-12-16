#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "FFT.h"

int main(int argc, char **argv)
{
    int a = 4;
    int b = index_reverse(3, a);
    printf("test : %d -> %d", a, b);
    return 0;
}
