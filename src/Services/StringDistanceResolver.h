#include <string>
#include "../Helpers/Matrix.h"
using string = std::string;

class StringDistanceResolver
{
private:
    /* data */
public:
    StringDistanceResolver(/* args */);

    int get_leventshtein_distance(string, string);

    void calculate_steps(Matrix &);

    void prefill_levenshtein(Matrix &);
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_leventshtein_distance(string str_l, string str_r)
{

    auto matrix = Matrix(str_l, str_r);
#pragma omp parallel
    {
        prefill_levenshtein(matrix);
        calculate_steps(matrix);
    }
    return matrix.final_distance();
}

void StringDistanceResolver::calculate_steps(Matrix &matrix)
{
    auto data = matrix.raw();
    auto rows = matrix.rows();
    auto cols = matrix.cols();

    for (int i = 1; i < rows; i++)
    {

#pragma omp parallel for
        for (int j = 1; j < cols; j++)
        {
            data[i][j] = data[i - 1][j];

            if (data[i][j] > data[i][j - 1])
            {
                data[i][j] = data[i][j - 1];
            }

            if (data[i][j] > data[i - 1][j - 1])
            {
                data[i][j] = data[i - 1][j - 1];
            }

            if (matrix.l_str()[i - 1] != matrix.r_str()[j - 1])
            {
                data[i][j]++;
            }
        }
    }
}

void StringDistanceResolver::prefill_levenshtein(Matrix &matrix)
{
    auto data = matrix.raw();

#pragma omp parallel for
    for (int i = 0; i < matrix.rows(); i++)
    {
        data[i][0] = i;
    }

#pragma omp parallel for
    for (int i = 0; i < matrix.cols(); i++)
    {
        data[0][i] = i;
    }
}
