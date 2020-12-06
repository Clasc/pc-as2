class Matrix
{
private:
    string _l_str;
    string _r_str;
    int **_matrix;

public:
    Matrix(string l_str, string _r_str);
    ~Matrix();

    int cols() const;
    int rows() const;
    int **raw() const;
    string l_str() const;
    string r_str() const;
    int final_distance() const;
    string to_string() const;
};

Matrix::Matrix(string l_str, string r_str)
{
    _l_str = l_str;
    _r_str = r_str;
    _matrix = new int *[rows()];
#pragma openmp parallel for
    for (int i = 0; i < rows(); i++)
    {
        _matrix[i] = new int[cols()];
    }
}

Matrix::~Matrix()
{
#pragma openmp parallel for
    for (int i = 0; i < rows(); ++i)
        delete[] _matrix[i];
    delete[] _matrix;
}

int Matrix::rows() const
{
    return this->_l_str.length() + 1;
}

int Matrix::cols() const
{
    return this->_r_str.length() + 1;
}

int **Matrix::raw() const
{
    return _matrix;
}

int Matrix::final_distance() const
{
    return _matrix[rows() - 1][cols() - 1];
}

string Matrix::l_str() const
{
    return _l_str;
}

string Matrix::r_str() const
{
    return _r_str;
}

string Matrix::to_string() const
{
    string str = "[\n";
    for (int i = 0; i < rows(); i++)
    {
        for (int j = 0; j < cols(); j++)
        {
            str += std::to_string(_matrix[i][j]);
            str += ",";
        }
        str += '\n';
    }
    str += "]";
    return str;
}