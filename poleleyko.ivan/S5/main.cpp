#include <iostream>
#include <fstream>
#include <binary_tree.hpp>
#include "key_summer.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Invalid number of arguments\n";
        return 1;
    }

    poleleyko::StringTreeMap stringMap;
    std::ifstream inputFile(argv[2]);

    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file\n";
        return 2;
    }

    poleleyko::readInput(inputFile, stringMap);
    if (!inputFile.eof())
    {
        std::cerr << "Error in file format\n";
        return 3;
    }

    poleleyko::Tree<std::string, std::function<void(std::ostream&, const poleleyko::StringTreeMap&, KeySummer&)>> commandMap;
    commandMap["ascending"] = poleleyko::ascendTraversal;
    commandMap["descending"] = poleleyko::descendTraversal;
    commandMap["breadth"] = poleleyko::breadthTraversal;

    try
    {
        std::string command(argv[1]);
        poleleyko::KeySummer keySummer;
        commandMap.at(command)(std::cout, stringMap, keySummer);
        std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
        std::cerr << "Invalid command\n";
        return 1;
    }
    catch (const std::logic_error& e)
    {
        std::cout << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 4;
    }

    return 0;
}
