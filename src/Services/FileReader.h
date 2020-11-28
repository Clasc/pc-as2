#include <string>
#include <fstream>
#include <sstream>
using string = std::string;

class FileReader
{
private:
    /* data */
public:
    FileReader();
    string get_content(string);
};

FileReader::FileReader(/* args */)
{
}

string FileReader::get_content(string file_path)
{
    std::ifstream file_stream(file_path);
    string str;
    if (!file_stream)
    {
        return "";
    }

    std::ostringstream string_stream;
    string_stream << file_stream.rdbuf();
    str = string_stream.str();
    return str;
}
