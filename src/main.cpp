#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <omp.h>
#include "Services/FileReader.h"

int main(int argc, char *argv[])
{
    int size = 20;
    int *array = new int[size];

    if (!argv || !argv[1] || !argv[2])
    {
        throw std::invalid_argument("Pass to filenames as Arguments for comparison.");
    }

    FileReader reader = FileReader();
    auto lfile_content = reader.get_content(argv[1]);
    auto rfile_content = reader.get_content(argv[2]);

    std::cout << lfile_content << std::endl;
    std::cout << rfile_content << std::endl;

    // #pragma omp parallel for
    //     for (int i = 0; i < size; i++)
    //     {
    //         array[i] = i;
    //     }

    //     for (int i = 0; i < size; i++)
    //     {
    //         std::cout << array[i];
    //     }

    delete[] array;

    return 0;
}