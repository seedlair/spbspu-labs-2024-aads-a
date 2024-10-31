#include "inputfile.hpp"

void poleleyko::readInput(std::istream& inputStream, StringTreeMap& stringMap)
{
    std::string identifier;
    while (inputStream >> identifier)
    {
        long long keyValue;
        std::string value;
        BinaryTree binaryTree;

        while (inputStream >> keyValue >> value)
        {
            if (inputStream.fail())
            {
                inputStream.clear(); // Сбрасываем флаг ошибок
                break;
            }
            binaryTree.insert({keyValue, value});
        }
        stringMap.insert({identifier, binaryTree});
    }
}
