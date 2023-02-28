#include <stdio.h>

int main(void)
{
    int c=0;
    int d=3;
    printf("%i    %i \n", d, c);

    d = c;

    printf("%i    %i \n", d, c);
}