#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>

namespace zxt
{
    /*
    int array[] = { 1, 2, 3, 4 };
    std::string content = zxt::join(array, ",");
    */
    template<typename Container>
    std::string join(const Container& container, const std::string& sep)
    {
        bool is_first = true;
        std::ostringstream oss;
        std::for_each(std::begin(container), std::end(container),
            [&oss, &is_first, &sep](auto& item) mutable {
            oss << (is_first ? "" : sep) << item;
            is_first = false;
        });
        return oss.str();
    }
    /*
    int array[] = { 1, 2, 3, 4 };
    std::string content = zxt::join<int>(array, ",");
    */
    template<typename Item, typename Container>
    std::string join(const Container& container, const std::string& sep)
    {
        bool is_first = true;
        std::ostringstream oss;
        std::for_each(std::begin(container), std::end(container),
            [&oss, &is_first, &sep](const Item& item) mutable {
            oss << (is_first ? "" : sep) << item;
            is_first = false;
        });
        return oss.str();
    }
    /*
    std::string filename = "file.dat";
    std::string content;
    zxt::filename2content(filename, content);
    */
    static void filename2content(const std::string& filename, std::string& content)
    {
        std::copy(std::istreambuf_iterator<char>(std::ifstream(filename, std::ios_base::in | std::ios_base::binary).rdbuf()), std::istreambuf_iterator<char>(), std::back_inserter(content));
    }
}

namespace zxt
{
    template<typename Type>
    std::string to_string(Type _val)
    {
        return std::to_string(_val);
    }
    std::string to_string(char _val, bool isNum = false)
    {
        //basic_string(size_type _Count, _Elem _Ch)
        return isNum ? std::to_string(int(_val)) : std::string(1, _val);
    }
    std::string to_string(const char* _val)
    {
        return (nullptr == _val) ? "" : _val;
    }
    std::string to_string(const std::string& _val)
    {
        return _val;
    }
};
