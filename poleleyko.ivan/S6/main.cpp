#include <map>
#include <iomanip>
#include <utility>
#include <functional>

#include "sortprocess.hpp"
#include "sorting_algorithms.hpp"

int main(int argc, char *argv[])
{
    using namespace poleleyko;  // Изменено пространство имен
    if (argc != 4)
    {
        std::cerr << "Invalid input\n";
        return 1;
    }
    
    size_t elementCount = 0;
    try
    {
        elementCount = std::stoull(argv[3]);
    }
    catch (...)
    {
        std::cerr << "Invalid parameter\n";
        return 1;
    }
    
    if (elementCount == 0)
    {
        std::cerr << "Invalid size\n";
        return 1;
    }

    std::map<std::pair<std::string, std::string>, std::function<void(size_t, std::ostream&)>> commands;
    commands[std::make_pair("asc", "floats")] = processSorting<float, std::less<float>>;
    commands[std::make_pair("desc", "floats")] = processSorting<float, std::greater<float>>;
    commands[std::make_pair("asc", "ints")] = processSorting<int, std::less<int>>;
    commands[std::make_pair("desc", "ints")] = processSorting<int, std::greater<int>>;

    std::cout << std::fixed << std::setprecision(1);
    try
    {
        commands.at(std::make_pair(std::string(argv[1]), std::string(argv[2])))(elementCount, std::cout);
    }
    catch (...)
    {
        std::cerr << "Execution error\n";
        return 1;
    }
}
