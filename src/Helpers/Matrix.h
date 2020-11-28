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
};

Matrix::Matrix(int rows, int cols)
{
    this->_cols = cols;
    this->_rows = rows;
    _matrix = new int *[_cols];
    for (int i = 0; i < _cols; i++)
    {
        _matrix[i] = new int[_rows];
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
