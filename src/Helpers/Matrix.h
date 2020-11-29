class Matrix
{
private:
    int _rows;
    int _cols;
    int **_matrix;

public:
    Matrix(int rows, int cols);
    ~Matrix();

    int cols() const;
    int rows() const;
    int **raw() const;

    string to_string() const;
};

Matrix::Matrix(int rows, int cols)
{
    this->_cols = cols;
    this->_rows = rows;
    _matrix = new int *[_rows];
    for (int i = 0; i < _rows; i++)
    {
        _matrix[i] = new int[_cols];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < _rows; ++i)
        delete[] _matrix[i];
    delete[] _matrix;
}

int Matrix::rows() const
{
    return this->_rows;
}

int Matrix::cols() const
{
    return this->_cols;
}

int **Matrix::raw() const
{
    return _matrix;
}

string Matrix::to_string() const
{
    string str = "[\n";
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            str += std::to_string(_matrix[i][j]);
            str += ",";
        }
        str += '\n';
    }
    str += "]";
    return str;
}