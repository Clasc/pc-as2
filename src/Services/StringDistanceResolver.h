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
    int get_min(int a, int b, int c);
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

    for (int j = 0; j < cols; j++)
    {
        distance = j + 1;

        for (int i = 1; i < rows; i++)
        {

            auto new_dist = get_min(distance, i - 1, vector[i - 1]);

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

int StringDistanceResolver::get_distance_two_vec(string str_l, string str_r)
{
    auto rows = str_l.length() + 1;
    auto cols = str_r.length() + 1;
    auto distance = 0;

    std::vector<int> v0 = std::vector<int>(rows);
    std::vector<int> v1 = std::vector<int>(cols);

    // initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance for an empty s
    // the distance is just the number of characters to delete from t
    for (int i = 0; i < rows; i++)
    {
        v0[i] = i;
    }

    for (int i = 0; i < cols - 1; i++)
    {
        // calculate v1 (current row distances) from the previous row v0

        // first element of v1 is A[i+1][0]
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 1;

        // use formula to fill in the rest of the row
        for (int j = 0; j < rows - 1; j++)
        {
            // calculating costs for A[i+1][j+1]

            v1[j + 1] = get_min(v0[j + 1] + 1, v1[j] + 1, v0[j]);

            if (str_l[i] != str_r[j])
            {
                v1[j + 1]++;
            }
            // copy v1 (current row) to v0 (previous row) for next iteration
            // since data in v1 is always invalidated, a swap without copy could be more efficient
        }
        //swap v0 with v1
        v0 = v1;
        // after the last swap, the results of v1 are now in v0
    }
    return v0[rows];
}

int StringDistanceResolver::get_min(int a, int b, int c)
{
    auto result = a < b ? a : b;
    result = result < c ? result : c;
    return result;
}