#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <omp.h>
#include <chrono>
#include "Services/FileReader.h"
#include "Services/StringDistanceResolver.h"

int main(int argc, char *argv[])
{
    int size = 20;

    if (!argv || !argv[1] || !argv[2])
    {
        throw std::invalid_argument("Pass to filenames as Arguments for comparison.");
    }

    FileReader reader = FileReader();

    auto lfile_content = reader.get_content(argv[1]);
    auto rfile_content = reader.get_content(argv[2]);

    auto t1 = std::chrono::high_resolution_clock::now();

    auto resolver = StringDistanceResolver();
    auto distance = resolver.get_distance_vec(lfile_content, rfile_content);
    //auto distance = resolver.get_distance_matrix(lfile_content, rfile_content);

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << distance << std::endl;
    std::cout << std::chrono::duration<double>(t2 - t1).count() << std::endl;

    return 0;
}