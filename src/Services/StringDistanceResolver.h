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
    void parallel_for_loop(std::vector<bool> &, std::vector<int> &, int, int, int, string, string, bool);

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

    std::vector<int> previous_row = std::vector<int>(cols);
    std::vector<bool> is_locked = std::vector<bool>(rows);
#pragma omp parallel for
    for (int i = 0; i < cols; i++)
    {
        previous_row[i] = i;
    }

#pragma omp parallel for
    for (int i = 0; i < rows; i++)
    {
        is_locked[i] = true;
    }

    is_locked[0] = false;

#pragma omp parallel num_threads(2)
    {
#pragma omp task
        {
            parallel_for_loop(is_locked, previous_row, rows, 0, cols / 2, str_l, str_r, true);
        }

#pragma omp task
        {
            parallel_for_loop(is_locked, previous_row, rows, cols / 2, cols, str_l, str_r, false);
        }
    }

    distance = previous_row[cols - 1];
    return distance;
}

void StringDistanceResolver::parallel_for_loop(std::vector<bool> &is_locked, std::vector<int> &previous_row, int rows, int from, int to, string str_l, string str_r, bool is_leading_thread = true)
{
    for (int i = 0; i < rows; ++i)
    {

        if (!is_leading_thread)
        {
            while (is_locked[i])
            {
                // wait
                //std::cout << "thread is waiting" << omp_get_thread_num() << std::endl;
            }
        }

        auto last_substitution = i;
        auto last_insert = i + 1;
        for (int j = from; j < to; j++)
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

        is_locked[i + 1] = false;
    }
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