#include <string>
#include <vector>
using string = std::string;

class StringDistanceResolver
{
private:
    /* data */
public:
    StringDistanceResolver(/* args */);

    int get_distance_vec(string, string);
    int get_distance_two_vec(string, string);
    int get_distance_matrix(string, string);
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_distance_vec(string str_l, string str_r)
{
    auto rows = str_l.length() + 1;
    auto cols = str_r.length();
    auto vector = std::vector<int>(rows);
    auto distance = 0;

#pragma omp parallel for
    for (int j = 0; j < cols; j++)
    {
        distance = j + 1;

        for (int i = 1; i < rows; i++)
        {

            auto new_dist = distance;

            if (new_dist > i - 1)
            {
                new_dist = i - 1;
            }

            if (new_dist > vector[i - 1])
            {
                new_dist = vector[i - 1];
            }

            if (str_l[i - 1] != str_r[j])
            {
                new_dist++;
            }

            vector[i - 1] = distance;
            distance = new_dist;
        }

        vector[rows - 1] = distance;
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
            matrix[i][j] = matrix[i - 1][j];

            if (matrix[i][j] > matrix[i - 1][j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1];
            }

            if (matrix[i][j] > matrix[i][j - 1])
            {
                matrix[i][j] = matrix[i][j - 1];
            }

            if (str_l[i - 1] != str_r[j - 1])
            {
                matrix[i][j]++;
            }
        }
    }

    return matrix[rows - 1][cols - 1];
}