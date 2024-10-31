#include "keysum.hpp"
#include <limits>
#include <stdexcept>

bool isOverflow(int lhs, int rhs)
{
    int minVal = std::numeric_limits<int>::min();
    int maxVal = std::numeric_limits<int>::max();
    return (lhs > 0 && maxVal - lhs < rhs) || (lhs < 0 && rhs < 0 && minVal - lhs > rhs);
}

poleleyko::KeySummer::KeySummer() : concatenatedValues(), keySum(0) {}

void poleleyko::KeySummer::operator()(const std::pair<int, std::string>& element)
{
    if (!element.second.empty())
    {
        concatenatedValues += " " + element.second;
    }

    if (isOverflow(keySum, element.first))
    {
        throw std::overflow_error("Overflow detected");
    }

    keySum += element.first;
}

int poleleyko::KeySummer::getKeySum() const
{
    return keySum;
}

std::string poleleyko::KeySummer::getValueString() const
{
    return concatenatedValues;
}
