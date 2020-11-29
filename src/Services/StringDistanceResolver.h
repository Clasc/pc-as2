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
    auto cols = str_l.length();
    auto rows = str_r.length();
    auto matrix = Matrix(rows, cols);
    prefill_levenshtein(matrix);
    calculate_steps(matrix);
    std::cout << matrix.to_string();
    return -1;
}

void StringDistanceResolver::calculate_steps(Matrix &matrix)
{
    auto data = matrix.raw();
    for (int i = 1; i < matrix.rows(); i++)
    {
        for (int j = 1; j < matrix.cols(); j++)
        {
            data[i][j] = data[i - 1][j];
            data[i][j] = data[i][j] < data[i][j - 1] ? data[i][j] : data[i - 1][j];
            data[i][j] = data[i][j] < data[i - 1][j - 1] ? data[i][j] : data[i - 1][j - 1];
            data[i][j]++;
        }
    }
}

void StringDistanceResolver::prefill_levenshtein(Matrix &matrix)
{
    auto data = matrix.raw();

    for (int i = 0; i < matrix.rows(); i++)
    {
        data[i][0] = i;
    }

    for (int i = 0; i < matrix.cols(); i++)
    {
        data[0][i] = i;
    }
}
