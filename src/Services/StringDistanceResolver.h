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
};

StringDistanceResolver::StringDistanceResolver(/* args */)
{
}

int StringDistanceResolver::get_leventshtein_distance(string str_l, string str_r)
{
    auto cols = str_l.length();
    auto rows = str_r.length();
    auto matrix = Matrix(rows, cols);

    return -1;
}
