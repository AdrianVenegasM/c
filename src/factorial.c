#include <Clearning/factorial.h>
#include <stdlib.h>
#include <stdio.h>

int factorial(int number)
{
    int result = 1;
    
    for (int i = 1; i <= number; ++i)
    {
        result *= i;
    }
    FILE *fp = fopen("file.txt", "r");
    
    return result;
}
