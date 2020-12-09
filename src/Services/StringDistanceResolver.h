#include <string>
#include <vector>
using string = std::string;

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

    std::vector<int> previous_row = std::vector<int>(cols);

    for (int i = 0; i < cols; i++)
    {
        previous_row[i] = i;
    }

    for (int i = 0; i < rows; i++)
    {
        auto last_subs_cost = i;
        auto last_insert_cost = i + 1;

        for (int j = 0; j < cols; j++)
        {
            auto deletion = previous_row[j];
            last_insert_cost = get_min(last_insert_cost, last_subs_cost, deletion);

            if (str_l[i] != str_r[j])
            {
                last_insert_cost++;
            }

            last_subs_cost = deletion;
            previous_row[j] = last_insert_cost;
        }
    }

    return previous_row[cols - 1];
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