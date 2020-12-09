#include <string>
#include <vector>
#include <thread>
#include <chrono>

using string = std::string;
using namespace std::chrono_literals;

class StringDistanceResolver
{
private:
    void print(std::vector<int>);

public:
    StringDistanceResolver(/* args */);

    int get_distance_vec(string, string);
    int get_distance_matrix(string, string);
    int get_min(int a, int b, int c);
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_distance_vec(string str_l, string str_r)
{
    auto rows = str_l.length();
    auto cols = str_r.length();

    auto distance = 0;

#pragma omp parallel num_threads(4)
    {
        std::vector<int> previous_row = std::vector<int>(cols);

        for (int i = 0; i < cols; i++)
        {
            previous_row[i] = i;
        }

#pragma omp parallel num_threads(2)
        {
            auto shared_col = std::vector<int>(rows);
#pragma omp single
            {
                shared_col[0] = 0;
                for (int i = 1; i < rows; i++)
                {
                    shared_col[i] = -1;
                }
            }

#pragma omp for schedule(static)
            for (int i = 0; i < rows; ++i)
            {
                auto shared_col_val = i == 0 ? 0 : shared_col[i - 1];
                while (shared_col_val == -1)
                {
                    // std::this_thread::sleep_for(100ms);
                    // std::cout << "thread waits for index: " << i << "\n";
                }

                // std::cout << "thread not watiting for index: " << i << "\n";

                auto last_substitution = i;
                auto last_insert = i + 1;
                for (int j = 0; j < cols; j++)
                {
                    auto deletion = previous_row[j];
                    last_insert = get_min(last_insert, last_substitution, deletion);

                    if (str_l[i] != str_r[j])
                    {
                        last_insert++;
                    }

                    last_substitution = deletion;
                    previous_row[j] = last_insert;
                }

                // std::cout << "Finished calculating first row:" << previous_row[cols - 1] << std::endl;
                shared_col[i] = previous_row[cols - 1];
            }

            distance = shared_col[rows - 1];
        }
    }
    return distance;
}

int StringDistanceResolver::get_distance_matrix(string str_l, string str_r)
{
    auto rows = str_l.length() + 1;
    auto cols = str_r.length() + 1;
    auto distance = 0;
    std::vector<std::vector<int>> matrix(str_l.length() + 1);

    for (int i = 0; i < rows; i++)
    {
        matrix[i].resize(cols + 1);
    }

    for (int i = 1; i < rows; i++)
    {
        matrix[i][0] = i;
    }

    for (int i = 1; i < cols; i++)
    {
        matrix[0][i] = i;
    }

    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            auto replace = matrix[i - 1][j - 1];
            auto insert = matrix[i][j - 1];
            auto deletion = matrix[i - 1][j];

            auto current_operation = get_min(replace, insert, deletion);

            if (str_l[i - 1] != str_r[j - 1])
            {
                current_operation++;
            }

            matrix[i][j] = current_operation;
        }
    }

    return matrix[rows - 1][cols - 1];
}

int StringDistanceResolver::get_min(int a, int b, int c)
{
    auto result = a < b ? a : b;
    result = result < c ? result : c;
    return result;
}

void StringDistanceResolver::print(std::vector<int> vector)
{
    std::string str = "[\n";
    for (const auto &e : vector)
    {
        str.append(std::to_string(e));
        str.append(",");
    }
    str.append("]");
    std::cout << "vec: " << str << std::endl;
}