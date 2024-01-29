#include <stdio.h>

int add_int(int num1, int num2)
{
    return num1 + num2;
}

float add_float(float num1, float num2)
{
    return num1 + num2;
}

// gcc -shared -fPIC add.c -o add.c.so