#include <vector>
#include <string>

class Data
{
private:
    string _l_str;
    string _r_str;

public:
    Data(string l_str, string _r_str);
    ~Data();

    int cols() const;
    int rows() const;

    string l_str() const;
    string r_str() const;
    int final_distance() const;
    string to_string() const;
};

Data::Data(string l_str, string r_str)
{
    _l_str = l_str;
    _r_str = r_str;
}

Data::~Data()
{
}

int Data::rows() const
{
    return this->_l_str.length() + 1;
}

int Data::cols() const
{
    return this->_r_str.length();
}

string Data::l_str() const
{
    return _l_str;
}

string Data::r_str() const
{
    return _r_str;
}
