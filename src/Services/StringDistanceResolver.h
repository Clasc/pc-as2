#include <string>
#include <vector>
using string = std::string;

class StringDistanceResolver
{
private:
    /* data */
public:
    StringDistanceResolver(/* args */);

    int get_leventshtein_distance(string, string);
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_leventshtein_distance(string str_l, string str_r)
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
