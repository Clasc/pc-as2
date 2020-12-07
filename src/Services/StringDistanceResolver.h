#include <string>
#include "../Helpers/Data.h"
using string = std::string;

class StringDistanceResolver
{
private:
    /* data */
public:
    StringDistanceResolver(/* args */);

    int get_leventshtein_distance(string, string);

    int calculate_steps(Data &);
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_leventshtein_distance(string str_l, string str_r)
{

    auto matrix = Data(str_l, str_r);
    int distance;
#pragma omp parallel
    {
        distance = calculate_steps(matrix);
    }
    return distance;
}

int StringDistanceResolver::calculate_steps(Data &data)
{
    auto rows = data.rows();
    auto cols = data.cols();
    auto vector = std::vector<int>(rows);
    auto distance = 0;

#pragma omp parallel for
    for (int j = 0; j < cols; j++)
    {
        distance = j + 1;

        for (int i = 1; i < rows; i++)
        {

            auto new_dist = vector[i - 1] < i - 1 ? vector[i - 1] : i - 1;

            if (data.l_str()[i - 1] != data.r_str()[i - 1])
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
