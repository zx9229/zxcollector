#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>

namespace zxt
{
    /*
    int array[] = { 1,2,3,4 };
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

    static void filename2content(const std::string& filename, std::string& content)
    {
        std::copy(std::istreambuf_iterator<char>(std::ifstream(filename, std::ios_base::in | std::ios_base::binary).rdbuf()), std::istreambuf_iterator<char>(), std::back_inserter(content));
    }
}
