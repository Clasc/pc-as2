#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <omp.h>

int main(int, char *[])
{
    int size = 20;
    int *array = new int[size];

#pragma omp parallel
    {
        std::cout << " test \n";
    }

    return 0;
}